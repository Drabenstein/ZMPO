#pragma once

static const double MIN_ITEM_VALUE = 1.0;
static const double MAX_ITEM_VALUE = 20.0;
static const double MIN_ITEM_SIZE = 1.0;
static const double MAX_ITEM_SIZE = 10.0;
static const int KNAPSACK_ITEMS_COUNT = 10;
static const int POP_SIZE = 10;
static const int TOURNAMENT_SIZE = 2;
static const int ITERATIONS_NUM = 1000;
static const double MUTATION_PROBABILITY = 0.1;
static const double CROSSOVER_PROBABILITY = 0.6;
static const double KNAPSACK_CAPACITY = 10.0;

static const std::string ERR_MSG_INVALID_CROSSOVER_PROBABILITY = "Invalid crossover probability value";
static const std::string ERR_MSG_INVALID_MUTATION_PROBABILITY = "Invalid mutation probability value";
static const std::string ERR_MSG_INVALID_ITERATIONS_NUM = "Invalid iterations value";
static const std::string ERR_MSG_INVALID_POPULATION_SIZE = "Invalid population size";
static const std::string ERR_MSG_INVALID_SUBJECT_VALUE = "At least one of the subjects has invalid value";
static const std::string ERR_MSG_INVALID_SUBJECT_SIZE = "At least one of the subjects has invalid size";
static const std::string ERR_MSG_INVALID_MAX_SIZE = "Invalid knapsack's capacity";
static const std::string ERR_MSG_INVALID_TOURNAMENT_SIZE = "Invalid tournament size";
static const std::string ERR_MSG_UNKNOWN_ERROR = "Unknown error";
static const std::string ERR_MSG_NO_BEST_RESULT = "The best result could not be found";