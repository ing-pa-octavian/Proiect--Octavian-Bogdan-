#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Masina {
    string marca;
    string model;
    int an;
    float pret;
    string culoare;
};

struct Garanție {
    int ani;
    float pret;
};

void afisareMasini(const vector<Masina>& masini) {
    for (const auto& masina : masini) {
        cout << "Marca: " << masina.marca
             << "  Model: " << masina.model
             << "  An: " << masina.an
             << "  Pret: $" << masina.pret
             << "  Culoare: " << masina.culoare << endl;
    }
}

void bubbleSortPret(vector<Masina>& masini) {
    int n = masini.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (masini[j].pret > masini[j + 1].pret) {
                swap(masini[j], masini[j + 1]);
            }
        }
    }
}

int partition(vector<Masina>& masini, int low, int high) {
    int pivot = masini[high].an;
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (masini[j].an < pivot) {
            ++i;
            swap(masini[i], masini[j]);
        }
    }
    swap(masini[i + 1], masini[high]);
    return i + 1;
}

void quickSortAn(vector<Masina>& masini, int low, int high) {
    if (low < high) {
        int pi = partition(masini, low, high);
        quickSortAn(masini, low, pi - 1);
        quickSortAn(masini, pi + 1, high);
    }
}

void negociazaPret(vector<Masina>& masini) {
    int index = rand() % masini.size();
    Masina& masina = masini[index];

    cout << "Negociere pentru masini: "
         << masina.marca << " " << masina.model
         << ", An: " << masina.an
         << ", Pret initial: $" << masina.pret << "\n";

    float oferta;
    cout << "Introduceti oferta dupa placul vostru: ";
    cin >> oferta;

    if (oferta >= masina.pret * 0.9) {
        cout << "Felicitari! Oferta dvs. de $" << oferta << " a fost acceptata!\n";
        masina.pret = oferta;


        Garanție garantie;
        cout << "Alegeti numarul de ani pentru garantie (1-5): ";
        cin >> garantie.ani;


        switch (garantie.ani) {
            case 1:
                garantie.pret = 500;
                break;
            case 2:
                garantie.pret = 900;
                break;
            case 3:
                garantie.pret = 1200;
                break;
            case 4:
                garantie.pret = 1500;
                break;
            case 5:
                garantie.pret = 1800;
                break;
            default:
                cout << "Optiune invalida! Nu se va adauga garantie.\n";
                return;
        }

        cout << "Garanția de " << garantie.ani
             << " ani a fost adaugata la pretul masinii. "
             << "Pret total cu garantie: $"
             << masina.pret + garantie.pret
             << endl;

        masina.pret += garantie.pret;
    } else {
        cout << "Oferta este prea mica, pretul ramine: $" << masina.pret << "\n";
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    vector<Masina> masini = {
      {"BMW", "X5", 2019, static_cast<float>(rand() % 30000 + 10000), "Negru"},
      {"Audi", "A4", 2022, static_cast<float>(rand() % 30000 + 10000), "Alb"},
      {"Mercedes", "C-Class", 2020, static_cast<float>(rand() % 30000 + 10000), "Argintiu"},
      {"Toyota", "Corolla", 2018, static_cast<float>(rand() % 30000 + 10000), "Rosu"},
      {"Ford", "Focus", 2021, static_cast<float>(rand() % 30000 + 10000), "Albastru"}
    };

    cout << "Masini initiale: \n";
    afisareMasini(masini);

    bubbleSortPret(masini);
    cout << "\nMasinile sortate dupa pret (Bubble Sort): \n";
    afisareMasini(masini);

    quickSortAn(masini, 0, masini.size() - 1);
    cout << "\nMasini sortate dupa anul fabricatiei (Quick Sort): \n";
    afisareMasini(masini);

    negociazaPret(masini);

    cout << "\nLista actualizata de masini dupa negociere: \n";
    afisareMasini(masini);

    return 0;
}