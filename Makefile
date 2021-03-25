SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := .
EXE := $(BIN_DIR)/a.exe
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
CXX := clang++
CXXFLAGS := -Iinclude -Wall -g
LDFLAGS := 
LDLIBS := -lmingw32 -lSDL2main -lSDL2_image -lSDL2


$(EXE): $(OBJ)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(EXE)
	/c/"Program Files"/PowerShell/7-preview/pwsh -c "wt -d . cmd /k a.exe"
