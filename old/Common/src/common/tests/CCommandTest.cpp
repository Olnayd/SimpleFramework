
#include "common/tests/CCommandTest.hpp"
#include <common/api/Operation.hpp>

/************************************************
 * UseCase 1
 ************************************************
 * Check Op Statuses
 */
TEST_F (CCommandTest, UseCase_1_1)
{
  Operation op;
  ASSERT_FALSE (op.isPending ());
  ASSERT_TRUE (op.isFinished ());
  ASSERT_FALSE (op.isAborted ());
}

TEST_F (CCommandTest, UseCase_1_2)
{
  Operation op;
  op.setPending ();
  ASSERT_TRUE (op.isPending ());
  ASSERT_FALSE (op.isFinished ());
  ASSERT_FALSE (op.isAborted ());
}

TEST_F (CCommandTest, UseCase_1_3)
{
  Operation pendingOp;
  pendingOp.setPending ();

  Operation op;
  op.join (pendingOp);
  ASSERT_TRUE (op.isPending ());
  ASSERT_FALSE (op.isFinished ());
  ASSERT_FALSE (op.isAborted ());
}

TEST_F (CCommandTest, UseCase_1_4)
{
  Operation op;
  op.finish ();
  ASSERT_FALSE (op.isPending ());
  ASSERT_TRUE (op.isFinished ());
  ASSERT_FALSE (op.isAborted ());
}

TEST_F (CCommandTest, UseCase_1_5)
{
  Operation op;
  op.abort ();
  ASSERT_FALSE (op.isPending ());
  ASSERT_TRUE (op.isFinished ());
  ASSERT_TRUE (op.isAborted ());
}

/************************************************
 * Use case 4
 ************************************************
 * Check Join
 */

/*
 * Use Case 4.1
 * Check join of empty op
 */
TEST_F (CCommandTest, UseCase_4_1)
{
  Operation emptyOp;

  Operation op;
  op.join (emptyOp);
  ASSERT_FALSE (op.isPending ());
  ASSERT_TRUE (op.isFinished ());
  ASSERT_FALSE (op.isAborted ());

  bool bCalled{ false };
  op.onFinish ([&bCalled] () { bCalled = true; });
  ASSERT_TRUE (bCalled);
}

/*
 * Use Case 4.2
 * Check join of pending op
 */
TEST_F (CCommandTest, UseCase_4_2)
{
  Operation pendingOp;
  pendingOp.setPending ();

  Operation op;
  op.join (pendingOp);
  ASSERT_TRUE (op.isPending ());
  ASSERT_FALSE (op.isFinished ());
  ASSERT_FALSE (op.isAborted ());

  bool bCalled{ false };
  op.onFinish ([&bCalled] () { bCalled = true; });
  ASSERT_FALSE (bCalled);

  pendingOp.finish ();
  ASSERT_TRUE (bCalled);
}

/************************************************
 * Use case 5
 ************************************************
 * Check Abort
 */

/*
 * Use Case 5.1
 * Check abort of empty op
 */
TEST_F (CCommandTest, UseCase_5_1)
{
  Operation op;
  op.abort ();
  ASSERT_FALSE (op.isPending ());
  ASSERT_TRUE (op.isFinished ());
  ASSERT_TRUE (op.isAborted ());
}

/*
 * Use Case 5.2
 * Check abort of pending op
 */
TEST_F (CCommandTest, UseCase_5_2)
{
  Operation op;
  op.setPending ();
  op.abort ();
  ASSERT_FALSE (op.isPending ());
  ASSERT_TRUE (op.isFinished ());
  ASSERT_TRUE (op.isAborted ());
}

/*
 * Use Case 5.3
 * Check abort of joined op
 */
TEST_F (CCommandTest, UseCase_5_3)
{
  Operation pendingop;
  pendingop.setPending ();

  Operation op;
  op.join (pendingop);
  op.abort ();
  ASSERT_FALSE (op.isPending ());
  ASSERT_TRUE (op.isFinished ());
  ASSERT_TRUE (op.isAborted ());
}

/************************************************
 * Use case 6
 ************************************************
 * Check OnFinish
 */

/***
 * Use Case 6.1:
 * Operation is empty.
 ***
 * Expected:
 * OnFinish should be called instantly
 */
TEST_F (CCommandTest, UseCase_6_1)
{
  bool bCalled{ false };
  Operation op;
  op.onFinish ([&bCalled] () { bCalled = true; });
  ASSERT_TRUE (bCalled);
}

/***
 * Use Case 6.2:
 * Operation is pending.
 ***
 * Expected:
 * OnFinish should not be called
 */
TEST_F (CCommandTest, UseCase_6_2)
{
  bool bCalled{ false };
  Operation op;
  op.setPending ();
  op.onFinish ([&bCalled] () { bCalled = true; });
  ASSERT_FALSE (bCalled);
}

/***
 * Use Case 6.3:
 * Operation waits for another pending op
 ***
 * Expected:
 * OnFinish should not be called
 */
TEST_F (CCommandTest, UseCase_6_3)
{
  bool bCalled{ false };
  Operation joinedOp;
  joinedOp.setPending ();

  Operation op;
  op.join (joinedOp);
  op.onFinish ([&bCalled] () { bCalled = true; });
  ASSERT_FALSE (bCalled);
}

/***
 * Use Case 6.4:
 * Operation is pending and waits for another pending Op
 ***
 * Expected:
 * OnFinish should not be called
 */
TEST_F (CCommandTest, UseCase_6_4)
{
  bool bCalled{ false };
  Operation joinedOp;
  joinedOp.setPending ();

  Operation op;
  op.join (joinedOp);
  op.setPending ();
  op.onFinish ([&bCalled] () { bCalled = true; });
  ASSERT_FALSE (bCalled);
}

/***
 * Use Case 6.5:
 * Abort of pending Op
 ***
 * Expected:
 * OnFinish should be called
 */
TEST_F (CCommandTest, UseCase_6_5)
{
  bool bCalled{ false };
  Operation op;
  op.setPending ();
  op.abort ();
  op.onFinish ([&bCalled] () { bCalled = true; });
  ASSERT_TRUE (bCalled);
}

/***
 * Use Case 6.6:
 * Abort of joined op
 ***
 * Expected:
 * OnFinish should not be called
 */
TEST_F (CCommandTest, UseCase_6_6)
{
  bool bCalled{ false };
  Operation joinedOp;
  joinedOp.setPending ();

  Operation op;
  op.join (joinedOp);
  op.onFinish ([&bCalled] () { bCalled = true; });
  ASSERT_FALSE (bCalled);
}

/***
 * Use Case 6.7:
 * Operation is pending and waits for another pending Op
 ***
 * Expected:
 * OnFinish should not be called
 */
TEST_F (CCommandTest, UseCase_6_7)
{
  bool bCalled{ false };
  Operation joinedOp;
  joinedOp.setPending ();

  Operation op;
  op.join (joinedOp);
  op.setPending ();
  op.onFinish ([&bCalled] () { bCalled = true; });
  ASSERT_FALSE (bCalled);
}

/***
 * Use Case 6.8:
 **
 * Precondition:
 * Operation is pending and waits for another pending Op
 **
 * Action:
 * Finish operation
 ***
 * Expected:
 * OnFinish should not be called due joined pending operation
 */
TEST_F (CCommandTest, UseCase_6_8)
{
  bool bCalled{ false };
  Operation joinedOp;
  joinedOp.setPending ();

  Operation op;
  op.join (joinedOp);
  op.setPending ();
  op.onFinish ([&bCalled] () { bCalled = true; });
  op.finish ();
  ASSERT_FALSE (bCalled);
}

/***
 * Use Case 6.9:
 **
 * Precondition:
 * Operation is pending and waits for another pending Op
 **
 * Action:
 * Finish joined operation
 ***
 * Expected:
 * OnFinish should not be called due to operation still pending
 */
TEST_F (CCommandTest, UseCase_6_9)
{
  bool bCalled{ false };
  Operation joinedOp;
  joinedOp.setPending ();

  Operation op;
  op.join (joinedOp);
  op.setPending ();
  op.onFinish ([&bCalled] () { bCalled = true; });
  joinedOp.finish ();
  ASSERT_FALSE (bCalled);
}

/***
 * Use Case 6.10:
 **
 * Precondition:
 * Operation is pending and waits for another pending Op
 **
 * Action:
 * Finish operation and joined operation
 ***
 * Expected:
 * OnFinish should be called.
 */
TEST_F (CCommandTest, UseCase_6_10)
{
  int number{ 0 };
  Operation joinedOp;
  joinedOp.setPending ();

  Operation op;
  op.join (joinedOp);
  op.setPending ();
  op.onFinish ([&number] () { ++number; });
  joinedOp.finish ();
  op.finish ();
  ASSERT_TRUE (number);
  ASSERT_TRUE (number == 1);
}

/***
 * Use Case 6.11:
 **
 * Precondition:
 * Operation is pending and waits for another pending Op
 **
 * Action:
 * Abort and then Finish operation and joined operation
 ***
 * Expected:
 * OnFinish should be called once at abort.
 */
TEST_F (CCommandTest, UseCase_6_11)
{
  bool bCalled{ false };
  Operation joinedOp;
  joinedOp.setPending ();

  Operation op;
  op.join (joinedOp);
  op.setPending ();
  op.onFinish ([&bCalled] () { bCalled = true; });
  op.abort ();
  ASSERT_TRUE (bCalled);

  bCalled = false;
  joinedOp.finish ();
  ASSERT_FALSE (bCalled);
  op.finish ();
  ASSERT_FALSE (bCalled);
}

/***
 * Use Case 6.12:
 **
 ***
 * Expected:
 * OnFinish should be called once
 */
TEST_F (CCommandTest, UseCase_6_12)
{
  bool bCalled{ false };
  Operation op;
  op.setPending ();
  op.onFinish ([&bCalled] () { bCalled = true; });

  bCalled = false;
  op.finish ();
  ASSERT_TRUE (bCalled);

  bCalled = false;
  op.finish ();
  ASSERT_FALSE (bCalled);
}

/***
 * Use Case 6.13:
 **
 ***
 * Expected:
 * OnFinish should be called once
 */
TEST_F (CCommandTest, UseCase_6_13)
{
  bool bCalled{ false };
  Operation op;
  op.setPending ();
  op.onFinish ([&bCalled] () { bCalled = true; });

  bCalled = false;
  op.abort ();
  ASSERT_TRUE (bCalled);

  bCalled = false;
  op.finish ();
  ASSERT_FALSE (bCalled);
}
