class Door {
 public:
  Door() {}
  virtual bool isLocked() = 0;
  ~Door() {}
};