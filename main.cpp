#include "DataTreatment.h"

int main()
{
    //Nome do arquivo de entrada, nome do dono do perfil, quantidade de amigos
    DataTreatment sample("result_give_me_my _data.txt", "Marcel Augusto" , 82);
    sample.setRelations();
    sample.toMatrix();
    sample.friendList();
    return 0;
}
