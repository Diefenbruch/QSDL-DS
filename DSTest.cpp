#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>

#include "DSRef.h"
#include "DSBlock.h"
#include "DSFormalParamList.h"
#include "DSList.h"
#include "DSObjectStack.h"
#include "DSString.h"
#include "DSSystem.h"
#include "DSVariable.h"

#ifdef DEBUG
#include <dmalloc.h>
#endif

int main(void)
{
  int i;

  DSString format_test;

  DSStringRefList string_list;

  DSFormalParamList wurst1, wurst2;

  DSString t1("1"), t2("2"), t3("3"), t4("4"), t5("5");

  cout << "String-cout Test: " << t1 << endl;

  format_test.Format("%s : %d : %f : %s", "Hallo", 123, 5.8, t1.GetString());
  cout << "Format-Test 1: " << format_test << endl;

  format_test.Format("%s : %d : %f : %s", "Hallo", 123, 5.8, t1.GetString());
  cout << "Format-Test 2: " << format_test << endl;

  string_list.Append(&t1);
  string_list.Append(&t2);
  string_list.Append(&t3);
  string_list.Append(&t4);
  string_list.Append(&t5);

  DSSystem system("Testname");
  DSString string("Hallo");
  DSBlock *block_ptr;

  DSBlockKeyList *block_list = new DSBlockKeyList;
  DSObjectStack *block_stack = new DSObjectStack;

  char str[80];

  for (i = 1;
       i <= 10;
       i++)
  {
    sprintf(str, "Block %d", i);
    block_ptr = new DSBlock(&system, str);

    block_stack->Push(block_ptr);
    block_list->Append(block_ptr, new DSString(*block_ptr->GetName()));
  }

  i = 0;

  for (block_ptr = system.GetFirstBlock();
       block_ptr != NULL;
       block_ptr = system.GetNextBlock())
  {
    i++;
    cout << i << ". Block: " << block_ptr->GetName() << '\n';
  }

  while(block_stack->Top() != NULL)
  {
    block_ptr = (DSBlock*)block_stack->Pop();
    assert(block_ptr != NULL);
    cout << "Top-Block: " << block_ptr->GetName() << '\n';
  }

  cout << *system.GetName() << '\n';

  delete block_stack;
  delete block_list;

  return 0;
}
