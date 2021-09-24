#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>

std::fstream bank("..\\src\\File\\ATM_info.txt", std::ios::app);
int numberBills;
int nominal[] = {100, 200, 500, 1000, 2000, 5000};

void fillingATM(){
  std::cout << "Filling the ATM" << std::endl;
  numberBills = 20; 
  int arr[1000];
  std::srand((time(NULL)));
  for(int i = 0; i < numberBills; ++i){
    if(arr[i] == 0){
      arr[i] = nominal[std::rand() % 6];
      bank << arr[i] << "\n";
    }
  }  
}

void removingBanknotes(){
  std::cout << "Removing banknotes" << std::endl;
  std::cout << "How much do you want to withdraw?" << std::endl;
  int money;
  std::cin >> money;
  if(money % 100 != 0){
    std::cerr << "Error data: " << money << std::endl;
  }else{
    int mas[1000];
    bank.read((char*)mas, sizeof(mas));
    int numberSpecies = sizeof(nominal) / sizeof(nominal[0]);
    std::vector<int> numbers(numberSpecies + 1, 0);
    for(int i = 0; i < numberBills; ++i){
      if(mas[i] == 5000) 
        ++numbers[5];
      else if(mas[i] == 2000) ++numbers[4];
      else if(mas[i] == 1000) ++numbers[3];
      else if(mas[i] == 500) ++numbers[2];
      else if(mas[i] == 200) ++numbers[1];
      else if(mas[i] == 100) ++numbers[0];
      // else ++numbers[0];
    }
  }
}

int main(){
  std::cout << "ATM" << std::endl;
  char action;
  if(bank.is_open() && bank.is_open()){
    std::cin >> action;
    if(action == '+'){      
      fillingATM();
    }else if(action == '-'){
      int size = 0;
      bank.seekg (0, std::ios::end);
      size = bank.tellg();
      if(size != 0){
        removingBanknotes();
      }else {
        std::cout << "The ATM is empty!!!" << std::endl;
      }
    }else{
      std::cout << "Errot action" << std::endl;
    }
  }else{
    std::cout << "Incorrect path: ATM_info.txt" << std::endl;
  }

  return 0;
}

// Требуется реализовать упрощённую симуляцию 
// работы банкомата. В банкомате могут 
// храниться только бумажные купюры номиналом 
// от 100 до 5000 рублей. Максимально в 
// банкомате может храниться только 1000 купюр. 
// Все они записываются в отдельный файл. 
// У банкомата, как у устройства, две основных 
// операции — снятие денег пользователем 
// и наполнение деньгами инкассаторами банка.

// Наполнение банкомата происходит, если 
// при старте программы в консоль вводится 
// символ плюс “+”.  Количество купюр 
// рассчитывается так, чтобы банкомат 
// был заполнен полностью. Все купюры 
// при этом выбираются случайным образом.

// Если на старте программы в консоль 
// вводится минус (“-”), то симулируется 
// снятие пользователем денег. Пользователь 
// указывает сумму с точностью до 100 рублей. 
// Мы будем считать, что каждый клиент 
// обладает неограниченным балансом в системе 
// и теоретически может снять любую сумму.
// На практике, если данная сумма не может 
// быть снята из-за отсутствия подходящих 
// денег в машине, показывается сообщение, 
// что эта операция невозможна.

// После выполнения любой из операций 
// программа завершает выполнение. 
// Состояние банкомата должно храниться в 
// отдельном бинарном файле, автономно.




// #include <iostream>
// #include <fstream>
// #include <cstdlib>
// #include <algorithm>
// #include <vector>

// int main() {
//   int nominal[] = {100, 200, 500, 1000, 2000, 5000};
//   std::ifstream bank("bank.bin", std::ios::binary);
//   if(!bank.is_open()){
//     std::cerr << "Incorrect path: bank.bin\n";
//     return 1;
//   }
//   int mas[1000];
//   bank.read((char*)mas, sizeof(mas));
//   bank.close();
//   const int numberBills = sizeof(mas) / sizeof(mas[0]);
//   const int numberSpecies = sizeof(nominal) / sizeof(nominal[0]);
//   std::cout << "Welcome to the bank!\nWhat operation do you want to perform? ";
//   char operation;
//   std::cin >> operation;
//   if(operation != '+' && operation != '-'){
//     std::cerr << "Error data!\n";
//     return 2;
//   }
//   if(operation == '+'){
//     for(int i = 0; i < numberBills; ++i){
//       if(mas[i] == 0){
//         mas[i] = nominal[std::rand() % 6];
//       }
//     }
//   }else{
//     std::cout << "How much do you want to withdraw money? ";
//     int number;
//     std::cin >> number;
//     if(number % 100 != 0){
//       std::cerr << "Error data: " << number << std::endl;
//       return 3;
//     }
//     std::vector<int> numbers(numberSpecies + 1, 0); //число купюр каждого номинала
//     std::vector<int> miracle(numberSpecies + 1, 0); //дубликат, с которым буду работать
//     std::sort(mas, mas + numberBills); //сортировка по возрастанию
//     for(int i = 0; i < numberBills; ++i){
//       if(mas[i] == 5000) ++numbers[6];
//       else if(mas[i] == 2000) ++numbers[5];
//       else if(mas[i] == 1000) ++numbers[4];
//       else if(mas[i] == 500) ++numbers[3];
//       else if(mas[i] == 200) ++numbers[2];
//       else if(mas[i] == 100) ++numbers[1];
//       else ++numbers[0];
//     }
//     for(int i = numberSpecies - 1;; --i){  
//       int cnt = 0;
// skip:
//       if(cnt == i) continue;
//       for(int j = 0; j < numbers.size(); ++j) miracle[j] = numbers[j];
//       int balance = number;
//       if(miracle[i + 1] == 0 || balance < nominal[i]) continue;
//       do{
//         balance -= nominal[i];
//         --miracle[i + 1];
//         ++miracle[0];
//       }while(!(miracle[i + 1] == 0 || balance < nominal[i]));
//       for(int j = i - cnt - 1; j >= 0; --j){
//         while(!(miracle[j + 1] == 0 || balance < nominal[j])){
//           balance -= nominal[j];
//           --miracle[j + 1];
//           ++miracle[0];
//         }
//       }
//       if(i == 0) break;
//       if(balance != 0){
//         ++cnt;
//         goto skip;
//       }else{
//         std::cout << "You have withdrawn " << number << std::endl;
//         number = balance;
//         break;
//       }
//     }
//     if(number != 0) std::cout << "Operation is not possible!";
//     int j = 0;
//     for(int i = 0; i <= numberSpecies; ++i){
//       for(int k = 1; k <= miracle[i]; ++k){
//         if(i == 0) mas[j] = 0;
//         else mas[j] = nominal[i - 1];
//         ++j;
//       }
//     }
//   }
//   std::ofstream out("bank.bin", std::ios::binary);
//   if(!out.is_open()){
//     std::cerr << "Incorrect path: bank.bin\n";
//     return 1;
//   }
//   out.write((char *) mas, sizeof(mas));
//   out.close();
//   return 0;
// }