#include <iostream>


#include "file.h"
#include "input_arguments_checker.h"
#include "signature_creator.h"

using std::cout;
using std::endl;
using std::to_string;


int main(int argc, const char** argv) {
  InputArgumentsChecker inputArgumentChecker(argc, argv);

  if (!inputArgumentChecker.IsInputParametersCorrect()) {
     cout << "Wrong input parameters" << endl; // add help description
      return 0;
  }

  if (inputArgumentChecker.IsSignatureCommand()) {
      const char* file_path = argv[2];
      File file(file_path);

      if (!file.isExists()) {
          cout << file_path << " doesn't exists. Can not create signature" << endl;
          return 0;
      }

      SignatureCreator signatureCreator;
      cout << "Signature: " << to_string(signatureCreator.getSignature(file)) << endl;
  }

  return 0;
}
