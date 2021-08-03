#ifndef COMMAND_HPP_
#define COMMAND_HPP_

#include <functional>
#include <memory>

class Operation
{
public:
  enum EResult
  {
    Success,
    Failed,
    Aborted
  };

private:
  struct SharedState;

public:
  Operation ();
  Operation (const Operation &);
  virtual ~Operation ();

  void setPending ();
  void finish ();
  void abort ();
  bool isPending () const;
  bool isAborted () const;
  bool isFinished () const;

  void setPayload (const std::shared_ptr<void> &);
  std::shared_ptr<void> getPayload () const;

  void onFinish (std::function<void (Operation)> &&);
  void onFinish (std::function<void ()> &&);

  /*
   * Joins another operation
   */
  Operation join (Operation &);
  Operation join (Operation &&);

private:
  bool isSharedStateExists () const;
  std::shared_ptr<SharedState> getSharedState () const;
  std::shared_ptr<SharedState> getOrCreateSharedState ();

private:
  std::shared_ptr<SharedState> mpSharedState;
};

#endif /* COMMAND_HPP_ */
