#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

int main(void)
{
    CU_basic_set_mode(CU_BRM_VERBOSE);

    extern CU_SuiteInfo singly_linked_list_test_suite;
    extern CU_SuiteInfo doubly_linked_list_test_suite;
    extern CU_SuiteInfo circular_singly_linked_list_test_suite;
    extern CU_SuiteInfo circular_doubly_linked_list_test_suite;
    extern CU_SuiteInfo array_list_test_suite;

    CU_SuiteInfo suites[] = 
    {
        singly_linked_list_test_suite,
        doubly_linked_list_test_suite,
        circular_singly_linked_list_test_suite,
        circular_doubly_linked_list_test_suite,
        array_list_test_suite,
        CU_SUITE_INFO_NULL
    };

    CU_initialize_registry();

    CU_register_suites(suites);

    CU_basic_run_tests();

    CU_cleanup_registry();
}