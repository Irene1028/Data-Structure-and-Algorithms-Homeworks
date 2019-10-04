#include "election.h"
//include any other headers you need here...
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

state_t parseLine(const char * line) {
  //STEP 1: write me
  state_t s = {" ", 0, 0};
  int i = 0;
  char num1[20] = {0};
  char num2[20] = {0};
  int m_first, m_second, a = 0;
  //char name[MAX_STATE_NAME_LENGTH];
  //find ':'s
  while (*(line + i) != '\0') {
    if (*(line + i) == ':') {
      if (a == 0) {
        m_first = i;
        a++;
      }
      else if (a == 1) {
        m_second = i;
        a++;
      }
      else {
        printf("This line has more than 2 ':'s!\n");
        exit(EXIT_FAILURE);
      }
    }
    i++;
  }

  //fill state name

  for (int j = 0; j < m_first; j++) {
    if (isalpha(*(line + j)) == 0 && *(line + j) != ' ') {
      printf("The state name is in wrong format!\n");
      exit(EXIT_FAILURE);
    }
    else {
      s.name[j] = *(line + j);
    }
    if (j == m_first) {
      s.name[j] = '\0';
    }
  }

  for (int j = m_first + 1; j < m_second; j++) {
    if (*(line + j) == '.') {
      printf("the population should not include decimal point!\n");
      exit(EXIT_FAILURE);
    }
    num1[j - m_first - 1] = *(line + j);
    if (j == m_second) {
      num1[j - m_first - 1] = '\0';
    }
  }

  for (int j = m_second + 1; j < i; j++) {
    if (*(line + j) == '.') {
      printf("the votes should not include decimal point!\n");
      exit(EXIT_FAILURE);
    }
    num2[j - m_second - 1] = *(line + j);
    if (j == i) {
      num2[j - m_second - 1] = '\0';
    }
  }

  int pop = atoi(num1);
  if (pop != 0) {
    s.population = pop;
  }
  else {
    printf("State population input is invalid!\n");
    exit(EXIT_FAILURE);
  }
  pop = atoi(num2);
  if (pop != 0) {
    s.electoralVotes = pop;
  }
  else {
    printf("State population input is invalid!\n");
    exit(EXIT_FAILURE);
  }

  return s;
}
unsigned int countElectoralVotes(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 2: write me
  unsigned int elct_cnt = 0;
  for (size_t i = 0; i < nStates; i++) {
    if (*(voteCounts + i) > 0.5 * (*(stateData + i)).population) {
      elct_cnt += (*(stateData + i)).electoralVotes;
    }
  }
  return elct_cnt;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 3: write me
  double vote_psnt = 0;

  for (size_t i = 0; i < nStates; i++) {
    vote_psnt = (*(voteCounts + i)) * 1.000 / (*(stateData + i)).population;

    if (vote_psnt > 0.495 && vote_psnt < 0.505) {
      printf("%s requires a recount (Candidate A has %.2f%% of the vote)\n",
             (*(stateData + i)).name,
             vote_psnt * 100);
    }
  }
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 4: write me
  double vote_psnt[nStates];
  double max = 0;
  int win_st_num = 0;
  for (size_t i = 0; i < nStates; i++) {
    vote_psnt[i] = (*(voteCounts + i)) * 1.000 / (*(stateData + i)).population;
    if (vote_psnt[i] > max) {
      max = vote_psnt[i];
      win_st_num = i;
    }
  }
  printf(
      "Candidate A won %s with %.2f%% of the vote\n", (*(stateData + win_st_num)).name, max * 100);
}
