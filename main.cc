#include <algorithm>
#include <cstdint>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
bool cmdOptionExists(char **begin, char **end, const std::string &option) {
  return std::find(begin, end, option) != end;
}
char *getCmdOption(char **begin, char **end, const std::string &option) {
  char **itr = std::find(begin, end, option);
  if (itr != end && ++itr != end) {
    return *itr;
  }
  return 0;
}
void append_to_file(std::string filepath, std::string to_append) {
  std::ofstream outf{filepath};
  if (!outf) {
    std::cerr << "Unable to open file for writing\n";
    return;
  }
  outf << to_append;
  return;
}
int32_t add_commit(std::string filepath, std::string message) {
  // git add .file
  // git commit -m "message"
  std::string addcmd = "git add ";
  addcmd = addcmd + filepath;
  int32_t result = system(addcmd.c_str());
  std::string commit = "git commit -m \'";
  std::string suffix = message + "\'";
  commit = commit + suffix;

  std::cout << commit << std::endl;

  return system(commit.c_str());
}

int32_t alter_authorDate(std::tm &timeInfo) {

  std::stringstream ss;
  ss << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S\'");
  std::string formattedTimeString = ss.str();
  std::string commitAmmend = "git commit --amend --no-edit --date=\'";
  commitAmmend = commitAmmend + formattedTimeString;

  std::cout << " === : " << commitAmmend << std::endl;

  return system(commitAmmend.c_str());
}
int32_t alter_commiterDate(std::tm &timeInfo) {
  std::stringstream ss;
  ss << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S\'");
  std::string formattedTimeString = ss.str();
  std::string commitAmmend = "GIT_COMMITTER_DATE=\'";
  commitAmmend =
      commitAmmend + formattedTimeString + " git commit --amend --no-edit";

  std::cout << commitAmmend << std::endl;

  return system(commitAmmend.c_str());
}
void modifyFile(std::string filepath, std::string appendthis) {
  std::ofstream outputFile(filepath, std::ios::app);
  if (outputFile.is_open()) {
    outputFile << appendthis << std::endl;

    outputFile.close();

  } else {
    std::cerr << "Error opening file" << std::endl;
  }
}

/*
 * 2010 calendar
 * Jan 3rd || Epoch timestamp : 1262488200
 * Dec 25th || Epoch timestamp : 1293246600
 */

/*
 * 2011 calendar
 * Jan 2nd || Epoch timestamp : 1293937800
 */

/*
 * * * * 0 0 0 0 * * 0 0 * * * 0 0 0 0 0 0 0 0 * * * 0 0 0 0 0 0 0 0 * * * * *
 * * * * * * * * * * * * * * *
 * * * * 0 0 0 0 * * 0 0 * * * 0 0 0 0 0 0 0 0 * * * 0 0 0 0 0 0 0 0 * * * * *
 * * * * * * * * * * * * * * *
 * * * * 0 0 0 0 0 * 0 0 * * * 0 * * * * * * * * * * 0 0 * * * * 0 0 * * * * *
 * * * * * * * * * * * * * * *
 * * * * 0 0 * 0 0 0 0 0 * * * 0 0 0 0 0 0 0 0 * * * 0 0 * * * * 0 0 * * * * *
 * * * * * * * * * * * * * * *
 * * * * 0 0 * * 0 0 0 0 * * * 0 * * * * * * * * * * 0 0 * * * * 0 0 * * * * *
 * * * * * * * * * * * * * * *
 * * * * 0 0 * * * * * * * * * 0 0 0 0 0 0 0 0 * * * 0 0 0 0 0 0 0 0 * * * * *
 * * * * * * * * * * * * * * *
 * * * * 0 0 * * * * * * * * * 0 0 0 0 0 0 0 0 * * * 0 0 0 0 0 0 0 0 * * * * *
 * * * * * * * * * * * * * * *
 */

// 1 week in unix epochs
// 604800
//
/*
 "****0000**00***00000000***00000000*******************\n
  ****0000**00***00000000***00000000*******************\n
  ****00000*00***0**********00****00*******************\n
  ****00*00000***00000000***00****00*******************\n
  ****00**0000***0**********00****00*******************\n
  ****00*********00000000***00000000*******************\n
  ****00*********00000000***00000000*******************\n\0"

 */

int main(int argc, char **argv) {

  char string_sequence[380] = "****0000**00***00000000***00000000**"
                              "*****************X****0000**00***000"
                              "00000***00000000******************"
                              "*X****00000*00***0**********00****00"
                              "*******************X****00*00000***0"
                              "0000000***00****00******************"
                              "*X****00**0000***0**********00****00"
                              "*******************X****00*********0"
                              "0000000***00000000******************"
                              "*X****00*********00000000***00000000"
                              "*******************X";
  // char *ptr_seq = &string_sequence[0];
  int count = 0;
  char ln_end = 'X';
  // uint32_t epoch = 1262488200;
  uint32_t epoch = 1293937800;
  uint32_t epoch_end = 1293246600;
  std::string filepath = "./README.md";
  uint32_t inner_epoch = epoch;
  while (380 > count) {
    inner_epoch = epoch;
    while (string_sequence[count] != 'X') {
      std::cout << string_sequence[count];
      if (string_sequence[count] == '0') {
        // git commit here with epoch
        std::cout << "git commit here with epoch";
        modifyFile(filepath, "anita max vynn \t");
        std::int32_t result = add_commit("./README.md", "not even randomized");
        if (result < 0) {
          std::cout << "commit failed" << std::endl;
          break;
        }
        std::time_t inner_time = (time_t)inner_epoch;
        std::tm timeInfo = *std::localtime(&inner_time);
        result = alter_authorDate(timeInfo);
        if (result < 0) {
          std::cout << "altering author date failed " << std::endl;
          break;
        }
        result = alter_commiterDate(timeInfo);
        if (result < 0) {
          std::cout << "alterning commit date failed " << std::endl;
          break;
        }
      }
      count += 1;
      inner_epoch += 604800;
    }
    epoch = epoch + 86400;
    count += 1;
  }
  return 0;
}
