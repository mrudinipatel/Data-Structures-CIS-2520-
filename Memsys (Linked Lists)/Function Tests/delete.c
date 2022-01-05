#include <stdio.h>
#include <string.h>

#include "list.h"
#include "memsys.h"

#define WIDTH 128

int main( int argc, char **argv )
{
  struct memsys *memsys;
  int one=1, two=2;
  struct Node node1, node2;

  int a_one, a_two, a_node1, a_node2;


  memsys = init(512,16);

  a_one = memmalloc( memsys, sizeof( one ) );
  a_two = memmalloc( memsys, sizeof( two ) );
  a_node1 = memmalloc( memsys, sizeof( node1 ) );
  a_node2 = memmalloc( memsys, sizeof( node2 ) );

  setval( memsys, &one, sizeof(int), a_one );
  setval( memsys, &two, sizeof(int), a_two );

  node1.data = a_one;
  node2.data = a_two;

  node1.next = a_node2;
  node2.next = MEMNULL;

  setval( memsys, &node1, sizeof(struct Node), a_node1 );
  setval( memsys, &node2, sizeof(struct Node), a_node2 );

  delete( memsys, &a_node1 );

  getval( memsys, &node1, sizeof(struct Node), a_node1 );

  if (node1.next!=MEMNULL)
  {
    printf( "Node not removed from previous" );
    return -1;
  }

  if (memsys->memctr.free!=2)
  {
    printf( "Memory not freed" );
    return -1;
  }

  printf( "ok" );
  return 0;
}


