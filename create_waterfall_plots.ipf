#pragma rtGlobals=3		// Use modern global access method and strict wave access.

function /S Create_Wave_Name_String()
	String prefix_name = "image0"
	String postfix_name = "dimoligos_3bases"
	
	Variable num_lanes = 8
	
	Variable i = 0
	String wavename_list =""
	for(i=0;i<=num_lanes;i+=1)
		String curr_wave_name = prefix_name + "_" + num2str(i) + "_" + postfix_name
		print(curr_wave_name)
		wavename_list+=curr_wave_name+";"
	endfor
	return(wavename_list)
end

function Correct_Background(lower_index,upper_index)
	Variable lower_index,upper_index
	String wavename_list = Create_Wave_Name_String()
	
	Variable num_lanes = ItemsInList(wavename_list)
	
	Variable i=0
	for(i=0;i<num_lanes;i+=1)
		String curr_lane_string = StringFromList(i,wavename_list)
		print(curr_lane_string)
		Wave curr_wave = $curr_lane_string
		Wavestats /Q /R=[lower_index,upper_index] curr_wave
		curr_wave -=V_avg
	endfor
end

function Make_Waterfall_Plot(lower_index,upper_index)
	Variable lower_index,upper_index
	String wavename_list = Create_Wave_Name_String()
	Variable num_lanes = ItemsInList(wavename_list)
	
	Variable num_pixels = (upper_index-lower_index+1)
	
	Make/O/N=(num_pixels,num_lanes) waterfall_matrix
	Variable i,j=0
	
	for(i=3;i<num_lanes;i+=1)
		String curr_lane_string = StringFromList(i,wavename_list)
		Wave curr_wave = $curr_lane_string
		for(j=0;j<num_pixels;j+=1)
			waterfall_matrix[j][i] = curr_wave[lower_index+j]
		endfor
	endfor
	
	
end

