#ifndef REGISTROANDINICIO_H_INCLUDED
#define REGISTROANDINICIO_H_INCLUDED

typedef struct
{
    char e_mail [100];
    char password [100];
    int valido; //1 o 0
    unsigned short int enter;
} Usuario;

Usuario iniciosesion(char archi []); /// inicia sesion para los usuarios ya registrados correctamente
void registroEnd(char archivo []);   /// registra a un nuevo usuario con mail y contraseña

#endif // REGISTROANDINICIO_H_INCLUDED
