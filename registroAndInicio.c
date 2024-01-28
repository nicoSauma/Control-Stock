#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "registroAndInicio.h"



Usuario iniciosesion(char archi [])
{
    FILE* buffer = fopen(archi, "rb");
    Usuario aux;
    int mailV, passV, flag = 0;
    char e_mailCheck[100];
    char passwordCheck[100];
    aux.enter = 0;


    if (buffer)
    {
        printf("Ingrese su mail: ");
        fflush(stdin);
        gets(e_mailCheck);

        printf("Ingrese su contrasena: ");
        fflush(stdin);
        gets(passwordCheck);

        while (flag == 0 && fread(&aux, sizeof(Usuario), 1, buffer))
        {
            if (aux.valido == 1)
            {
                mailV = strcmpi(e_mailCheck, aux.e_mail);

                if (mailV == 0)
                {
                    passV = strcmp(passwordCheck, aux.password);

                    if (passV == 0)
                    {
                        aux.enter = 1;
                        flag = 1;
                    }
                }
            }
        }

        fclose(buffer);
    }
    else
    {
        printf("No se pudo iniciar sesion.\n");
    }

    if (flag == 0)
    {
        aux.enter = 0;
    }


    return aux;
}




void registroEnd(char archivo [])
{
    FILE* buffer = fopen(archivo, "a+b");
    Usuario nuevo, aux;
    int valido = 1, flag = 0;
    char e_mailCheck[100];
    char passwordCheck[100];

    if (buffer)
    {
        do
        {
            flag = 0;

            do
            {
                if (valido == 0)
                {
                    printf("Ingrese un correo valido.\n\n");
                }
                printf("Ingrese su correo electronico: ");
                fflush(stdin);
                gets(nuevo.e_mail); //Pide el mail y lo guarda en la struct Usuario

                if (strstr(nuevo.e_mail, "@"))
                {
                    valido = 1; //Si tiene arroba sigue el registro
                }
                else
                {
                    valido = 0; //Si no tiene arroba, vuelve a pedir el mail
                }
                printf("\n");
            }
            while (valido == 0);

            do
            {
                printf("Ingreselo de vuelta para confirmar: "); //Confirmacion de mail
                fflush(stdin);
                gets(e_mailCheck);

                if (strcmpi(e_mailCheck, nuevo.e_mail) == 0)
                {
                    valido = 1; //Si es igual sigue con el registro
                }
                else
                {
                    valido = 0; //Si no es igual al mail anterior lo vuelve a pedir
                }
                printf("\n");
            }
            while (valido == 0);

            rewind(buffer);
            while(flag == 0 && fread(&aux, sizeof(Usuario), 1, buffer) > 0)
            {
                if(strcmp(nuevo.e_mail, aux.e_mail) == 0)
                {
                    flag = 1;
                    printf("Email ya existente\n");
                }
            }
        }
        while(flag == 1);
        fseek(buffer, 0, 2);

        do
        {
            if (valido == 0)
            {
                printf("\nERROR. Ingrese las contrasenas nuevamente\n");
            }
            printf("Ingrese su contrasena: ");
            fflush(stdin);
            gets(nuevo.password); //Guarda la contraseña en el struct Usuario

            printf("Ingrese de vuelta para confirmar: "); //Confirmacion de contraseña
            fflush(stdin);
            gets(passwordCheck);

            if (strcmp(nuevo.password, passwordCheck) == 0)
            {
                valido = 1; //Si las contraseñas son iguales, lo registra
            }
            else
            {
                valido = 0; //Si son diferentes vuelve a pedir ambas
            }
        }
        while (valido == 0);

        nuevo.valido = 1; //Valores por default de un usuario nuevo
       // nuevo.ad = 0;

        fwrite(&nuevo, sizeof(Usuario), 1, buffer); //Guarda el usuario en el archivo

        printf("\nSe ha registrado correctamente!\n\n");

        fclose(buffer);
    }
    else
    {
        printf("Hubo un error, no se pudo registrar.\n");
    }
}
