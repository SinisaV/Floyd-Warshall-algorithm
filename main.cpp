#include <iostream>
#include <fstream>

#define neskoncno 99999999

void meni() {
    std::cout << "Floyd-Warshallov algoritem - izbira:" << "\n";
    std::cout << "1) Preberi graf iz datoteke" << "\n";
    std::cout << "2) Zagon algoritma" << "\n";
    std::cout << "3) Izpis najkrajse poti med vozliscema s in g" << "\n";
    std::cout << "4) Konec" << "\n";
    std::cout << "Vasa izbira: ";
}

void grafSosednjosti(int **&C, int **&matrikaD, int **&matrikaPi, int &steviloVozlisc, int &steviloPovezav) {
    std::ifstream file("graf2.txt");

    int v1, v2, cena;

    file >> steviloVozlisc;
    file >> steviloPovezav;

    C = new int *[steviloVozlisc];
    matrikaD = new int *[steviloVozlisc];
    matrikaPi = new int *[steviloVozlisc];

    for (int i = 0; i < steviloVozlisc; i++) {
        C[i] = new int[steviloVozlisc];
        matrikaD[i] = new int[steviloVozlisc];
        matrikaPi[i] = new int[steviloVozlisc];
    }

    for (int i = 0;  i < steviloVozlisc; i++) {
        for (int j = 0;  j < steviloVozlisc; j++) {
            C[i][j] = 0; // napolnimo matriko s vrednostjo 0
        }
    }

    for (int i = 0; i < steviloPovezav; i++) { // napolnimo povezave s cenami
        file >> v1 >> v2 >> cena;
        C[v1 - 1][v2 - 1] = cena;
        C[v2 - 1][v1 - 1] = neskoncno; // povezava ne obstaja
    }

    std::cout << "MATRIKA SOSEDNJOSTI" << "\n";
    std::cout << "-------------------" << "\n";

    for (int i = 0;  i < steviloVozlisc; i++) {
        for (int j = 0;  j < steviloVozlisc; j++) {
            if (C[i][j] >= 10) {
                std::cout << C[i][j] << "  ";
            }
            else {
                std::cout << C[i][j] << "   ";
            }
        }
        std::cout << std::endl;
    }

}

void floydWarshall (int **&C, int **&matrikaD, int **&matrikaPi, int &steviloVozlisc) {
    for (int k = 0; k < steviloVozlisc; k++) {
        for (int l = 0; l < steviloVozlisc; l++) {
            matrikaD[k][l] = C[k][l]; // matrika D dobi vse vrednosti ki jih ima matrika C

            // ce vrednost v matriki ni 0 po diagonali in elementi matrike C niso neskoncno
            if (k != l && C[k][l] != neskoncno) {
                matrikaPi[k][l] = k; // dolocimo oceta
            }
            else {
                matrikaPi[k][l] = -1; // NIL
            }
        }
    }

    /*for (int i = 0;  i < steviloVozlisc; i++) {
        for (int j = 0;  j < steviloVozlisc; j++) {
            if (matrikaPi[i][j] >= 10) {
                std::cout << matrikaPi[i][j] << "  ";
            }
            else {
                std::cout << matrikaPi[i][j] << "   ";
            }
        }
        std::cout << std::endl;
    }*/

    for (int o = 0; o < steviloVozlisc; o++) {
        for (int m = 0; m < steviloVozlisc; m++) {
            for (int n = 0; n < steviloVozlisc; n++) {
                if (matrikaD[m][n] > matrikaD[o][n] + matrikaD[m][o]) { // ce je najdemo cenejso pot posodobimo matriko D
                    matrikaD[m][n] = matrikaD[o][n] + matrikaD[m][o];
                    matrikaPi[m][n] = matrikaPi[o][n]; // posodobimo matriko PI z novim predhodnikom
                }
            }
        }
    }

    /*for (int i = 0;  i < steviloVozlisc; i++) {
        for (int j = 0;  j < steviloVozlisc; j++) {
            if (matrikaPi[i][j] >= 10) {
                std::cout << matrikaPi[i][j] << "  ";
            }
            else {
                std::cout << matrikaPi[i][j] << "   ";
            }
        }
        std::cout << std::endl;
    }*/
}

void izpisPoti(int **&matrikaPi, int **&matrikaD, int s, int v) {
    if (v == s) {
        std::cout << "s => " << s << "\n";
    }
    else {
        if (matrikaPi[s][v] == -1) {
            std::cout << "Med " << s << " in " << v << + " ni poti" << "\n";
        }
        else {
            izpisPoti(matrikaPi, matrikaD, s, matrikaPi[s][v]);
            std::cout << "g => " << v << "\n";
            std:: cout << "Cena: " << matrikaD[s][v] << std::endl;
        }
    }
}

int main() {
    int **C = nullptr;
    int **matrikaD = nullptr;
    int **matrikaPi = nullptr;
    int steviloVozlisc = 0;
    int steviloPovezav = 0;

    int vozlisceS = 0, vozlisceV = 0;
    bool pogoj1 = false, pogoj2 = false;

    int selection;
    bool running = true;
    do {
        meni();
        std::cin >> selection;

        switch (selection) {
            case 1:
                grafSosednjosti(C, matrikaD, matrikaPi, steviloVozlisc, steviloPovezav);
                pogoj1 = true;
                break;
            case 2:
                if (pogoj1) {
                    floydWarshall(C, matrikaD, matrikaPi, steviloVozlisc);
                    pogoj1 = true;
                    pogoj2 = true;
                    break;
                }
                std::cout << "Prvo generiraj graf!" << "\n";
                pogoj1 = false;
                break;
            case 3:
                if (pogoj2) {
                    std::cout << "Vnesi zacetno vozlisce s: ";
                    std::cin >> vozlisceS;
                    std::cout << "Vnesi koncno vozlisce v: ";
                    std::cin >> vozlisceV;
                    izpisPoti(matrikaPi, matrikaD, vozlisceS, vozlisceV);
                    std::cout << "Skupna cena poti: " << matrikaD[vozlisceS][vozlisceV] << std::endl;
                    std::cout << "\n";
                    break;
                }
                else {
                    std::cout << "Prvo zazeni algoritem!" << "\n";
                    break;
                }
            case 4:
                running = false;
                break;
            default:
                std::cout << "Napacna izbira!\n";
                break;
        }
    } while(running);


    for (int i = 0; i < steviloVozlisc; i++) {
        delete [] C[i];
        delete [] matrikaD[i];
        delete [] matrikaPi[i];
    }
    delete [] C;
    delete [] matrikaD;
    delete [] matrikaPi;

    C = nullptr;
    matrikaD = nullptr;
    matrikaPi = nullptr;

    return 0;
}
