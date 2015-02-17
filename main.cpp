#include "DataTreatment.h"

int main()
{
    //Nome do arquivo de entrada, nome do dono do perfil, quantidade de amigos
    DataTreatment sample("Alexya_data.txt", "Alexya Beatriz" , 98);
    sample.setRelations();
    sample.toMatrix();
    sample.friendList();
    return 0;
}
