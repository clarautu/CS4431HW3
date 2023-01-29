// Autumn Clark
// Assignment 3
// Analysizes the pseudorandom number generator made in the last assignment

#include <iostream>
#include <cmath>
#include <vector> // Allows use of vectors
#include <fstream> // Allows reading and writing to files
using namespace std;

int const seed = 101101;
int lastNumReturned;
bool isFirstRun = true;
long int mod = pow(2,24);
long int period = 0;

//Function that returns the next random number from the LCG
long int randlcg(){
  long int pseudo;
  if(isFirstRun){
    pseudo = (61*seed + 1) % mod;
    isFirstRun = false;
  } else {
    pseudo = (61*lastNumReturned + 1) % mod;
  }
  lastNumReturned = pseudo;
  return pseudo;
}

//Function to normalize pseudorandom number to be between 0 and 1
float normalize(long int pseudo){
  float norm = (double(pseudo)/double(mod));
  return norm;
}

// Function that calculates the mean of the random numbers at the passed value
long int FindMean(long int num){
  isFirstRun = true; // First, reset the LCG
  long int mean = 0;
  // Find the mean of 100 numbers
  for(int i = 0; i < num; i++){
    mean += randlcg();
  }
  // Num is passed as a long to prevent the need to cast mean as a long
  mean = mean/num;
  return mean;

  // The mean at 100 is 7,266,414
  // The mean at 10,000 is 8,372,281
  // The mean at 1,000,000 is 8,389,083
  // The mean at 100,000,000 is 8,388,610

  /*
  The mean sits around 8.3 million for all the numbers except 100
  which sits around 7.2 million. Being that the mean stays very similar
  for the larger numbers, this LCG seems to do a pretty good job of
  producing 'random' numbers. I might also add that 8.3 million is
  roughly half of the LCG's period (which is also the maiximum number it
  can produce), so that is indicitive of an equal chance for any number
  to be produced. If it was a perfect random number generator, the mean
  would be half of the largest possible number, i.e. if the largest
  number that it could produce was 1,000,000 then the mean would
  be 500,000. Knowing that, I would say that our LCG is pretty good.
  */
}

// Function that writes bin data to files for
// 100, 10,000, 1,000,000, and 100,000,000 numbers
void BinLCG() {
  /* The below code writes the bin info to particular files
     the working directory. I have commented it out, as not
     having the specified text files will crash the code.

  // First 100 numbers
  vector<double> bins(100,0); // Create a vector to act as the bins
  isFirstRun = true; // Reset the LCG
  for(int i = 0; i < 100; i++){ // Loop through the first 100 numbers
    float rand = normalize(randlcg());
    // Multiply the normalized number by 100 to get the number between
    // 0 and 100, then cast as int to truncate value into the
    // appropiate index
    int index = static_cast<int>(rand*100);
    bins.at(index)++; // Increment the appropiate bin at index
  }
  ofstream file; // Assigns the filestream as file
  file.open("BinData100.txt"); // Open the appropiate file for number count
  file << "Bin\tNum\n"; // Add the column labels
  for(int i = 0; i < bins.size(); i++){
    // Loop through all the bins and write them to the file
    file << i << "\t" << bins.at(i) << "\n";
  }
  file.close(); // Close the file

  // Then 10,000 numbers
  fill(bins.begin(), bins.end(), 0); // Refill the vector with zeros
  isFirstRun = true; // Reset the LCG
  for(int i = 0; i < 10000; i++){
    float rand = normalize(randlcg());
    int index = static_cast<int>(rand*100);
    bins.at(index)++;
  }
  file.open("BinData10,000.txt");
  file << "Bin\tNum\n";
  for(int i = 0; i < bins.size(); i++){
    file << i << "\t" << bins.at(i) << "\n";
  }
  file.close();

  // Then 1,000,000 numbers
  fill(bins.begin(), bins.end(), 0);
  isFirstRun = true; // Reset the LCG
  for(int i = 0; i < 1000000; i++){
    float rand = normalize(randlcg());
    int index = static_cast<int>(rand*100);
    bins.at(index)++;
  }
  file.open("BinData1,000,000.txt");
  file << "Bin\tNum\n";
  for(int i = 0; i < bins.size(); i++){
    file << i << "\t" << bins.at(i) << "\n";
  }
  file.close();

  // Then 100,000,000 numbers
  fill(bins.begin(), bins.end(), 0);
  isFirstRun = true; // Reset the LCG
  for(int i = 0; i < 100000000; i++){
    float rand = normalize(randlcg());
    int index = static_cast<int>(rand*100);
    bins.at(index)++;
  }
  file.open("BinData100,000,000.txt");
  file << "Bin\tNum\n";
  for(int i = 0; i < bins.size(); i++){
    file << i << "\t" << bins.at(i) << "\n";
  }
  file.close();
  */
}

int main() {

  //The below code is to used to calculate the period of the LCG: 16,777,216
  float first = normalize(randlcg()); // Store the first number
  float next = 0; // Holds the next number to compare to the first number
  do { // Loop until the first number is reached again
    period++;
    next = normalize(randlcg());
    if (period == (mod + 1)){ // Checks to see if we have overflowed
      cout << "It overflowed. " << period << "\n";
    }
  } while (first != next); // The next number equals the first number -- period has been found
  cout << "The period is: " << period << endl;

  long int num;
  cout << "Enter a number to calulate the mean of the LCG at: ";
  cin >> num;
  cout << "\nThe mean of the LCG at " << num << " intervals is: "
     << FindMean(num) << endl;

 BinLCG();

  return 0;
}
