#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>

std::ofstream out ("..\\src\\File\\ATM.bin", std::ios::binary);
int nominal[] = {100, 200, 500, 1000, 2000, 5000};
int money[1000];

void fillingATM(){
  std::cout << "Filling the ATM" << std::endl;
    for(int i = 0; i < 1000; i++){
      if(money[i] == 0){
        money[i] = nominal[std::rand() % 6];
      }
    }    
    out.write((char *)money, sizeof(money)); 
}

void removingBanknotes(){
  std::cout << "Removing banknotes" << std::endl;
    std::cout << "How much do you want to withdraw?" << std::endl;
    int amount;
    std::cin >> amount;
    if(amount % 100 != 0){
    std::cerr << "Error data: " << amount << std::endl;
  }
  int amountCollect = amount;
  for(int i = 4; i >= 0; i--){
    int bill = nominal[i];
    for(int j = 0; j < 1000; j++){
      if(money[j] == bill){
        if(amountCollect >= bill){
          money[j] = 0;
          amountCollect -= bill;
          if(amountCollect == 0){
            std::cout << "Money taken " << amount << std::endl;
            out.write((char *)money, sizeof(money));
          }
        }
      }
    }
  }
    std::cerr << "ERROR taken money" << std::endl;
}

int main(){
  std::cout << "ATM" << std::endl;
std::cout << "Operation" << std::endl;
  std::string action;
    std::cin >> action;
  std::ifstream  bank("..\\src\\File\\ATM.bin", std::ios::binary);
  if(bank.is_open()){
    bank.read((char * ) money, sizeof(money));
    bank.close();
  }else{
    for(int i = 0; i < 1000; i++){
      money[i] = 0;
    }
  }
  if(action == "+"){
    fillingATM();
    return 0;
  }else if(action == "-"){
    removingBanknotes();

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
