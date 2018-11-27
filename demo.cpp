

#include <vector>
#include "csvtoker.hpp"

uint32_t gLoopCount = 2500000;

std::string TEST_LINE1 =
    "\"2016-03-22T21:17:01.701882+00:00\",\"vagrant-ubuntu-trusty-64\", 6,\"cron\",\"CRON[16538]:\",\" (root) CMD (   cd / && run-parts --report /etc/cron.hourly)\"";


void test_strtok()
{
  uint64_t total = 0;
  std::vector<std::string> result;
  for (int i=0; i < gLoopCount; i++) {
    result.clear();
    total += CsvToker::parse(TEST_LINE1, result);
  }
}

int main(int argc, char *argv[])
{
  if (argc > 1) {
    try {
      uint32_t val = atol(argv[1]);
      if (val > 0) {
        gLoopCount = val;
      }
    } catch (std::exception &e) {
      printf("Exception: %s\n", e.what());
    }
  }
  time_t tStart = time(NULL);
  //test_tokenizer();
  test_strtok();
  time_t tEnd = time(NULL);

  printf("DONE %u in %u sec\n", gLoopCount, (uint32_t)(tEnd-tStart));
}
