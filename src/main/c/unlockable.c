#include "unlockable.h"
#include <stdio.h>

typedef struct _unlockable {
  Unlockable obj;
  bool is_locked;
} _unlockable;

inline
static Unlockable *wrap(_unlockable *obj) {
  return (Unlockable *) obj;
}

inline
static _unlockable *unwrap(Unlockable *obj) {
  return (_unlockable *) obj;
}

Unlockable *unlockable_new(void (*unlock)(), void (*lock)(), char *(*get_data)()) {
  _unlockable *obj = (_unlockable*) malloc(sizeof(_unlockable));
  
  obj->is_locked = false;
  
  wrap(obj)->unlock = unlock;
  wrap(obj)->lock = lock;
  wrap(obj)->get_data = get_data;

  return wrap(obj);
}

bool unlockable_is_unlocked(Unlockable *unlockable) {
  return unwrap(unlockable)->is_locked ? false : true;
}

bool unlockable_is_locked(Unlockable *unlockable) {
  return unwrap(unlockable)->is_locked;
}

void unlockable_process_command(Unlockable *unlockable) {
  char *command = unlockable->get_data();
  if(strcmp(command, "unlock") == 0) {
    unlockable_unlock(unlockable);
  } else if(strcmp(command, "lock") == 0) {
      unlockable_lock(unlockable);
  }
}

void unlockable_lock(Unlockable *self) {
  unwrap(self)->is_locked = true;
  self->lock();
}

void unlockable_unlock(Unlockable *self) {
  unwrap(self)->is_locked = false;
  self->unlock();
}
