#include "input_proc.h"
#include "interaction_with_shape.h"

bool RecognitionInput(int key, Shape *current_s) {
	
	switch(key)
	{
		case LEFT: 		
			ChangeStartPoint(current_s, -1, 0); 
			break;
			
		case RIGHT: 	
			ChangeStartPoint(current_s, 1, 0); 	
			break;
		
		case DOWN: 		 
			ChangeStartPoint(current_s, 0, 1); 	
			break;
		
		case ENTER:
			ShapeRotation(current_s); 
			break; 
		
		case ESCAPE: 
			return true; 
			break;
	}

	return false;
}
