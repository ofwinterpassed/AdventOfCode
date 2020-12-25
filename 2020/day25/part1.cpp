#include <charconv>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {

  string line;
  getline(cin, line);
  long keypub;
  from_chars(line.data(), line.data() + line.size(), keypub);
  getline(cin, line);
  long doorpub;
  from_chars(line.data(), line.data() + line.size(), doorpub);

  long keyloop = 1;
  long acc = 1;
  while (acc != keypub) {
    acc = (acc * 7) % 20201227;
    ++keyloop;
  }
  --keyloop;

  cout << keyloop << '\n';

  long crypt = 1;
  for (long i = 0; i < keyloop; ++i)
    crypt = (crypt * doorpub) % 20201227;

  cout << crypt << '\n';

  long doorloop = 1;
  acc = 1;
  while (acc != doorpub) {
    acc = (acc * 7) % 20201227;
    ++doorloop;
  }
  --doorloop;

  cout << doorloop << '\n';

  crypt = 1;
  for (long i = 0; i < keyloop; ++i)
    crypt = (crypt * doorpub) % 20201227;

  cout << crypt << '\n';

  return 0;
}

