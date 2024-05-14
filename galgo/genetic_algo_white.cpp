#include "Galgo.hpp"
#include <unistd.h>
#include <fstream>
#include <stdio.h>
#include <string.h>
using namespace std;

// objective class example
template <typename T>
class MyObjective
{
public:
   static std::vector<T> Objective(const std::vector<T>& x)
   {
      pid_t pid = 0; //getpid();

      std::ofstream MyFile("/tmp/tablut/playerHeuristicWhite"+std::to_string(pid));
      MyFile << std::to_string(static_cast<int>(x[0])) + ","+  std::to_string(static_cast<int>(x[1])) +","+std::to_string(static_cast<int>(x[2])) +","+std::to_string(static_cast<int>(x[3]))+","+std::to_string(static_cast<int>(x[4])) << std::endl;
      MyFile.close();

      std::cout << std::to_string(pid) << std::endl;

      sleep(2);

      if(fork() == 0){
         system("cd /home/kali/Desktop/TablutCompetition/Tablut/Executables/ && java -jar Server.jar 5000 -g > server.txt");
         exit(0);
      }

      sleep(2);

      if(fork() == 0){
         system("/home/kali/Desktop/C++/vickynghi/cli/vickynghi BLACK -t 45 -j 4 -p trainingwhite > result.txt");
         exit(0);
      }

      system("/home/kali/Desktop/C++/vickynghi/cli/vickynghi WHITE -t 45 -j 4 -p trainingwhite > white.txt");

      string mytext;
      char * temp;
      int turn_count = 1;
      int white_count = 1;
      int black_count = 1;
      int white_win = 0;
      std::ifstream MyReadFile("/tmp/tablut/playerBlack"+std::to_string(pid));
      cout << "READING" << endl;
      while(getline(MyReadFile, mytext)){
         cout << mytext << endl;
         char *cstr = &mytext[0];

         temp = strtok(cstr,",");
         string s(temp);
         if (s.compare("WHITEWIN") == 0) {
            white_win = 1;
         }

         temp = strtok(NULL,",");
         turn_count = atoi(temp);

         temp = strtok(NULL,",");
         white_count = atoi(temp);

         temp = strtok(NULL,",");
         black_count = atoi(temp);
      }

      cout << "END READ" << endl;
      cout << white_win*(white_count + (16 - black_count) + (30 - turn_count)) << endl;
      T obj = white_win*(white_count + (16 - black_count) + (30 - turn_count));
      return {obj};
   }
};

// constraints example:
// 1) x * y + x - y + 1.5 <= 0
// 2) 10 - x * y <= 0
template <typename T>
std::vector<T> MyConstraint(const std::vector<T>& x)
{
   return {x[0]*x[1]+x[0]-x[1]+1.5,10-x[0]*x[1]};
}
// NB: a penalty will be applied if one of the constraints is > 0 
// using the default adaptation to constraint(s) method

int main()
{
   // initializing parameters lower and upper bounds
   // an initial value can be added inside the initializer list after the upper bound
   galgo::Parameter<float> HOT_AREA({-10,30,10});
   galgo::Parameter<float> MIDDLE_AREA({-10, 30, 5});
   galgo::Parameter<float> PURPLE({-10, 30, 5});
   galgo::Parameter<float> GREEN({-10, 30, 5});
   galgo::Parameter<float> MAGENTA({-10, 30, 5});

   // here both parameter will be encoded using 16 bits the default value inside the template declaration
   // this value can be modified but has to remain between 1 and 64

   // initiliazing genetic algorithm
   galgo::GeneticAlgorithm<float> ga(MyObjective<float>::Objective,3,3,true,HOT_AREA, MIDDLE_AREA, PURPLE, GREEN, MAGENTA);

   // setting constraints
   // ga.Constraint = MyConstraint;

   // running genetic algorithm
   ga.run();
   ga.result();
}