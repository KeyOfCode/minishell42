#include "../../minishell.h"

// IDEA de función para convertir la entrada de Bash a la salida expandida
// ejemplo, al expandir "Hola soy $USER, y mi home es $HOME"
// el resultado sería "Hola soy pedro, y mi home es /Users/pedro"

char *expand_bash_input(const char *input, char **env)
{
    int i;
    int j;
    int start;
    int end;
    char *output;
    char *expanded;
    char *var_name;

    if (!input || !env)
        return NULL;
    output = malloc(strlen(input) + 1);
    if (!output)
    {
        perror("Error de asignación de memoria");
        exit(EXIT_FAILURE);
    }
    i = 0;
    j = 0;
    while (input[i] != '\0') 
    {
        if (input[i] == '$')
        {
            // Buscar el nombre de la variable de entorno
            start = i + 1;
            end = start;
            while (input[end] != '\0' && (isalnum(input[end]) || input[end] == '_')) 
            {
                end++;
            }
            // Extraer el nombre de la variable de entorno
            var_name = malloc(end - start + 1);
            if (!var_name) 
            {
                perror("Error de asignación de memoria");
                exit(EXIT_FAILURE);
            }
            ft_strlcpy(var_name, input + start, end - start);
            var_name[end - start] = '\0';

            // Expandir la variable de entorno y copiar en el resultado
            expanded = expand_env(var_name, env);
            free(var_name);
            if (expanded) 
            {
                strcpy(output + j, expanded);
                j += strlen(expanded);
            } 
            else 
            {
                // Si no se puede expandir, copiar la parte original
                ft_strlcpy(output + j, input + i, end + 1);
                j += end + 1 - i;
            }
            i = end;
        }
        else
            output[j++] = input[i++];
    }
    output[j] = '\0';
    return output;
}

int main()
{
    char *env[] = {"USER=pedro", "HOME=/Users/pedro", NULL};
    const char *input = "Hola soy $USER, y mi home es $HOME";

    char *output = expand_bash_input(input, env);

    printf("Entrada: %s\n", input);
    printf("Salida expandida: %s\n", output);

    free(output);
    return 0;
}
