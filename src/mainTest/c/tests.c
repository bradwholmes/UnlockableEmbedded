#include <CUnit/Basic.h>
#include "gradle_cunit_register.h"
#include <stdio.h>
#include <stdlib.h>

#include "unlockable.h"

static char *command;
static Unlockable *unlockable;

int suite_init(void) {
  return 0;
}

int suite_clean(void) {
  command = NULL;
  free(unlockable);
  return 0;
}

void unlock_stub() {
}

void lock_stub() {
}

char *get_data_stub() {
  return command;
}

void initialize_lock(void) {
  unlockable = unlockable_new(unlock_stub, lock_stub, get_data_stub);
  
  CU_ASSERT(unlockable_is_unlocked(unlockable));
}

void lock(void) {
  unlockable = unlockable_new(unlock_stub, lock_stub, get_data_stub);
  unlockable_lock(unlockable);
  CU_ASSERT(unlockable_is_locked(unlockable));
}

void unlock_when_unlock_command_is_received(void) {
  command = "unlock";

  unlockable = unlockable_new(unlock_stub, lock_stub, get_data_stub);
  
  unlockable_lock(unlockable);

  unlockable_process_command(unlockable);

  CU_ASSERT(unlockable_is_unlocked(unlockable));
}

void lock_on_lock_command(void) {
  command = "lock";
  unlockable = unlockable_new(unlock_stub, lock_stub, get_data_stub);
  
  unlockable_process_command(unlockable);

  CU_ASSERT(unlockable_is_locked(unlockable));
}

void gradle_cunit_register() {
  CU_pSuite pSuite = CU_add_suite("test", suite_init, suite_clean);
  CU_add_test(pSuite, "Should initialize to an unlocked state", initialize_lock);
  CU_add_test(pSuite, "Should lock", lock);
  CU_add_test(pSuite, "Should unlock on command", unlock_when_unlock_command_is_received);
  CU_add_test(pSuite, "Should lock on command", lock_on_lock_command);
}
