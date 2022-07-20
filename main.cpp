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

  if (inputArgumentChecker.IsDeltaCommand()) {
      const char* base_file_path = argv[2];
      const char* new_file_path = argv[3];

      File base_file(base_file_path);
      File new_file(new_file_path);

      cout << "Base:\n" << base_file.getContent() << endl;
      cout << "New file:\n" << new_file.getContent() << endl;
  }

  return 0;
}
