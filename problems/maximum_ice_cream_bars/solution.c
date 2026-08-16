int maxIceCream(int* costs, int costsSize, int coins) {
    
  int max = 0;
  for ( int i = 0; i < costsSize; i++)
  {
    if ( costs[i] > max) max = costs[i];
  }

  int *sortcost = calloc(max + 1, sizeof *sortcost);

  for ( int i = 0; i < costsSize; i++)
  {
    sortcost[costs[i]]++;
  }
  
  int sum = 0;
  int count = 0;

  for (int i = 0; i < max + 1; i++) 
  {
    while (sortcost[i] > 0 && coins >= i)
    {
      coins -= i;
      count++;
      sortcost[i]--;
    }
  }
  return count;
  
}