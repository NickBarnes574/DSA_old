#include <check.h>

// This name matters
extern Suite *singly_linked_list_test_suite(void);
extern Suite *doubly_linked_list_test_suite(void);

int main(int argc, char** argv)
{
  // Suppress unused parameter warnings
  (void) argv[argc];

  // create test suite runner
  SRunner *sr = srunner_create(NULL);

  // prepare the test suites
  // the name in here matters
  srunner_add_suite(sr, singly_linked_list_test_suite());
  srunner_add_suite(sr, doubly_linked_list_test_suite());

  // run the test suites
  srunner_run_all(sr, CK_VERBOSE);

  // report the test failed status
  int tests_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  // return 1 or 0 based on whether or not tests failed
  return (tests_failed == 0) ? 0 : 1;
}
