#include <iostream>

void displayMenu(const std::string &info, const std::string &whatToGenerate,
                 const std::string &collectionOfWhat) //Menu dla problemu plecakowego i komiwojażera.
{
    std::cout << std::endl;
    std::cout << info << std::endl;
    std::cout << "1. Wczytaj z pliku." << std::endl;
    std::cout << "2. Wygeneruj " << whatToGenerate << " losowo." << std::endl;
    std::cout << "3. Wyświetl zbiór " << collectionOfWhat << "." << std::endl;
    std::cout << "4. Algorytm - zachłanny." << std::endl;
    std::cout << "5. Algorytm - zupełny." << std::endl;
    std::cout << "0. Powrot do menu." << std::endl;
    std::cout << "Podaj opcje: ";
}

void menu_discrete_knapsack_problem() //Obsługa problemu plecakowego.
{
    std::string path;
    int option;
    do {
        displayMenu("*** Problem plecakowy ***", "przedmioty", "przedmiotów");
        std::cin >> option;
        std::cout << std::endl;
        switch (option) {
            case 1: //Tworzenie zbioru przedmiotów z pliku txt.
                std::cout << "Podaj sciezke pliku z danymi: ";
                std::cin >> path;
                
                break;
            
            case 2: //Generowanie przedmiotów pseudolosowo.
                
                break;
            
            case 3: //Wyświetlanie zbioru przedmiotów.
                
                break;
            
            case 4: //Algorytm 1. - zachłanny..
                
                break;
            
            case 5: //Algorytm 2. - zupełny.
                
                break;
            
            default:
                break;
        }
        
    } while (option != 0);
}

void menu_travelling_salesman_problem() //Obsługa problemu komiwojażera.
{
    std::string path;
    int option;
    do {
        displayMenu("*** Problem komiwojażera ***", "miasta", "miast");
        std::cin >> option;
        std::cout << std::endl;
        switch (option) {
            case 1: //Tworzenie zbioru miast z pliku txt.
                std::cout << "Podaj sciezke pliku z danymi: ";
                std::cin >> path;
                
                break;
            
            case 2: //Generowanie miast pseudolosowo.
                
                break;
            
            case 3: //Wyświetlanie zbioru miast.
                
                break;
            
            case 4: //Algorytm 1. - zachłanny..
                
                break;
            
            case 5: //Algorytm 2. - zupełny.
                
                break;
            
            default:
                break;
        }
        
    } while (option != 0);
}

int main() {
    int option;
    do {
        std::cout << std::endl;
        std::cout << "==== MENU GŁÓWNE ===" << std::endl;
        std::cout << "1. Problem plecakowy." << std::endl;
        std::cout << "2. Problem komiwojażera." << std::endl;
        std::cout << "3. Testy czasowe." << std::endl;
        std::cout << "0. Wyjscie." << std::endl;
        std::cout << "Podaj opcje: ";
        std::cin >> option;
        std::cout << std::endl;
        
        switch (option) {
            case 1:
                menu_discrete_knapsack_problem();
                break;
            case 2:
                menu_travelling_salesman_problem();
                break;
            case 3:
                
                break;
        }
        
    } while (option != 0);
    
    return 0;
}