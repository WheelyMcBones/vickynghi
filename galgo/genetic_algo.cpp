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

      std::ofstream MyFile("/tmp/tablut/playerHeuristic"+std::to_string(pid));
      MyFile << std::to_string(static_cast<int>(x[0])) + ","+  std::to_string(static_cast<int>(x[1])) +","+std::to_string(static_cast<int>(x[2])) +","+std::to_string(static_cast<int>(x[3]))+","+std::to_string(static_cast<int>(x[4]))+","+std::to_string(static_cast<int>(x[5]))+","+std::to_string(static_cast<int>(x[6])) << std::endl;
      MyFile.close();

      std::cout << std::to_string(pid) << std::endl;

      sleep(2);

      if(fork() == 0){
         system("cd /home/kali/Desktop/TablutCompetition/Tablut/Executables/ && java -jar Server.jar 5000 -g > server.txt");
         exit(0);
      }

      sleep(2);

      if(fork() == 0){
         system("/home/kali/Desktop/C++/vickynghi/cli/osarracino WHITE -t 10 -j 1 > white.txt");
         exit(0);
      }

      system("/home/kali/Desktop/C++/vickynghi/cli/osarracino BLACK -t 10 -j 5 > result.txt");


      string mytext;
      char * temp;
      int turn_count = 1;
      int white_count = 1;
      int black_count = 1;
      int black_win = 0;
      std::ifstream MyReadFile("/tmp/tablut/playerBlack"+std::to_string(pid));
      cout << "READING" << endl;
      while(getline(MyReadFile, mytext)){
         cout << mytext << endl;
         char *cstr = &mytext[0];

         temp = strtok(cstr,",");
         string s(temp);
         if (s.compare("BLACKWIN") == 0) {
            black_win = 1;
         }

         temp = strtok(NULL,",");
         turn_count = atoi(temp);

         temp = strtok(NULL,",");
         white_count = atoi(temp);

         temp = strtok(NULL,",");
         black_count = atoi(temp);
      }

      cout << "END READ" << endl;
      cout << black_win*(black_count + (1 / (float)white_count) +(1 / (float)turn_count)) + 0.1 << endl;
      T obj = black_win*(black_count + (1 / (float)white_count) +(1 / (float)turn_count)) + 0.1;
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
   galgo::Parameter<float> HOT_AREA({0,40,10});
   galgo::Parameter<float> MIDDLE_AREA({0,20, 5});
   galgo::Parameter<float> COLD_AREA({0,10, 1});
   galgo::Parameter<float> PENALTY_FACTOR({-40,0, -5});
   galgo::Parameter<float> STRONG_MULT({20,60, 40});
   galgo::Parameter<float> LIGHT_MULT({0,20,10});

   // here both parameter will be encoded using 16 bits the default value inside the template declaration
   // this value can be modified but has to remain between 1 and 64

   // initiliazing genetic algorithm
   galgo::GeneticAlgorithm<float> ga(MyObjective<float>::Objective,3,3,true,HOT_AREA, MIDDLE_AREA, COLD_AREA, PENALTY_FACTOR, STRONG_MULT, LIGHT_MULT);

   // setting constraints
   // ga.Constraint = MyConstraint;

   // running genetic algorithm
   ga.run();
   ga.result();
}