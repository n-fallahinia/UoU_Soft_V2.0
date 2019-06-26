CXX = g++

# Include location for the header files
IDIR = include
MAGLEV_INC = include/maglev
OPENCV_INC = include/opencv
CXXFLAGS = $(patsubst %,-I%,$(IDIR)) $(patsubst %,-isystem%,$(MAGLEV_INC)) $(patsubst %,-isystem%,$(OPENCV_INC)) -Wall -ansi

# Define different directories
SDIR = src
ODIR = obj
LDIR = lib
BDIR = bin

# Include libraries for the Maglev driver
LIBS = -L$(LDIR) -lmlhi_api_linux
# Include libraries for camera drivers
LIBS += -ldc1394 -lraw1394 -pthread
# Include libraries for graphics
LIBS +=  -Lopencv -lopencv_core -lopencv_highgui -lopencv_cvv -lopencv_ximgproc -lopencv_imgproc 
# Include libraries for FLTK
LIBS += `fltk-config --ldflags --cxxflags --use-images --use-gl` -s -lcomedi -lm -lc -lrt -lGLU

# Define dependensies
_DEPS = CubeView Plot2DView BitOperating Graph3DAxis CameraControl Images Training ImageDisplay
_DEPS += MaglevControl ForceSensor maglev_parameters main
DEPS = $(patsubst %,$(IDIR)/%.h,$(_DEPS))

# Define object files
_OBJ = CubeView Plot2DView BitOperating Graph3DAxis CameraControl Images Training ImageDisplay
_OBJ += MaglevControl ForceSensor main
OBJ = $(patsubst %,$(ODIR)/%.o,$(_OBJ))

# Define target output file
TARGET := $(BDIR)/main

# Product:
all: $(TARGET)
	
$(info ==================== University of Utah ====================)
$(info ===================== Bio-Robotics Lab =====================)
$(info ============== Calibration Software GUI_ctc V2.1 ===========)
$(info )


# Rule to build regular .o files
$(ODIR)/%.o: $(SDIR)/%.cxx $(DEPS)
	@echo Building obj files
	$(CXX) -c -o $@ $< $(CXXFLAGS)

# Rule to build the target output file
$(TARGET): $(OBJ)
	@echo Building target output file:
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

.PHONY: clean
clean: 
	@echo cleaning objs
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
	rm -f $(TARGET)
