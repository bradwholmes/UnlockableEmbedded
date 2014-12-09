typedef enum {false, true} bool;

typedef struct unlockable {
  void (*unlock)();
  void (*lock)();
  
  char *(*get_data)();
} Unlockable;

Unlockable *unlockable_new(void (*)(), void(*)(), char *(*)());
bool unlockable_is_unlocked(Unlockable *self);
bool unlockable_is_locked(Unlockable *self);
void unlockable_process_command(Unlockable *self);
void unlockable_lock(Unlockable *self);
void unlockable_unlock(Unlockable *self);
