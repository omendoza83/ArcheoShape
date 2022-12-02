//=================================================================================================================
/**
 *  @file       qt_tools_exception_strings.h
 *  @brief      Definition of exception strings.
 *  @details    Definition file of the exception strings used to report errors in the qt_tools namespace.
 *  @author     Omar Mendoza Montoya (email: omendoz@live.com.mx).
 *  @copyright  Copyright (c) 2019 Omar Mendoza Montoya \n \n
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 *  associated documentation files (the "Software"), to deal in the Software without restriction,  
 *  including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,  
 *  and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, 
 *  subject to the following conditions: \n
 *  The above copyright notice and this permission notice shall be included in all copies or substantial 
 *  portions of the Software. \n
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 *  LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 *  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
//=================================================================================================================

#ifndef QT_TOOLS_EXCEPTION_STRINGS_H_INCLUDE
#define QT_TOOLS_EXCEPTION_STRINGS_H_INCLUDE

//=================================================================================================================
namespace qt_tools {

// Common errors.
inline constexpr const char* exc_unknown {"Unknown exception."};
inline constexpr const char* exc_operation_error_message {"Operation error: "};
inline constexpr const char* exc_operation_error_message_title {"Operation Error"};

inline constexpr const char* exc_two_variables_have_the_same_value {"Both variables are taking the same "
    "value, but they must not be equal to each other."};

inline constexpr const char* exc_arrays_of_different_lengths {"The arrays are of different lengths, but they "
    "must have the same number of elements."};

inline constexpr const char* exc_bad_array_size {"The size of the array is not valid for this operation."};

inline constexpr const char* exc_bad_bounds {"The specified values are not valid as lower and upper bounds."};

inline constexpr const char* exc_error_updating_interface {"Unable to update graphical interface."};
inline constexpr const char* exc_error_processing_file {"Unable to process file."};
inline constexpr const char* exc_error_updating_classification_model {"Unable to update classification model."};
inline constexpr const char* exc_error_validating_classification_model {"Unable to validate classification "
    "model."};
inline constexpr const char* exc_error_saving_file {"Unable to save file."};

// Strings for BCI tools.

inline constexpr const char* exc_bad_graphical_item_id {"The specified graphical item id is not valid."};
inline constexpr const char* exc_bad_graphical_item_state {"The specified graphical item state is not valid."};
inline constexpr const char* exc_bad_graphical_item_type {"The specified graphical item type is not valid."};
inline constexpr const char* exc_bad_flashing_method {"The specified flashing method is not valid."};

inline constexpr const char* exc_experiment_in_progress {"The experiment is in progress. Stop the experiment "
    "before changing the configuracion of the interface."};

inline constexpr const char* exc_graphical_item_id_already_in_object {"The specified graphical item id is "
    "being used by another object."};

// Strings for EEG tools.
inline constexpr const char* exc_empty_eeg_data {"The specified EEG data object is empty."};

inline constexpr const char* exc_bad_eeg_system_file {"Unable to read EEG system file."};

inline constexpr const char* exc_error_joining_eeg_epochs {"The source EEG epochs cannot be joined in "
    "a single file."};
inline constexpr const char* exc_error_joining_eeg_channels {"The source EEG channels cannot be joined "
    "in a single file."};
inline constexpr const char* exc_error_joining_eeg_bands {"The source EEG bands cannot be joined "
    "in a single file."};
inline constexpr const char* exc_error_joining_eeg_time_series {"The source EEG time series cannot be joined "
    "in a single file."};

inline constexpr const char* exc_bad_eeg_data_object {"The specified object does not contain valid EEG data."};
inline constexpr const char* exc_objects_with_trials_of_different_sizes {"The specified object does not contain "
    "valid EEG data."};

inline constexpr const char* exc_bad_epoch_index {"One ore more epoch indices are out of range."};
inline constexpr const char* exc_bad_channel_index {"One ore more channel indices are out of range."};
inline constexpr const char* exc_bad_band_index {"One ore more band indices are out of range."};

inline constexpr const char* exc_number_of_epochs_different_than_one {"The EEG data object must have one "
    "epoch exactly."};
inline constexpr const char* exc_number_of_bands_different_than_one {"The EEG data object must have one "
    "band exactly."};

inline constexpr const char* exc_non_real_valued_eeg_data {"The specified operation is only for "
    "real-valued EEG data."};
inline constexpr const char* exc_non_complex_eeg_data {"The specified operation is only for "
    "complex EEG data."};

inline constexpr const char* exc_empty_eeg_sample_range {"The specified sample range is empty."};

inline constexpr const char* exc_bad_band_range {"The specified range of bands is not valid."};
inline constexpr const char* exc_bad_band_threshold {"Band threshold must be lower than the number "
    "of bands."};
inline constexpr const char* exc_eeg_object_with_less_than_two_bands {"The EEG object must have at least "
    "two bands."};

inline constexpr const char* exc_two_eeg_groups_with_different_number_of_epochs {"Both groups of EEG trials "
    "must be of the same size."};

// Strings for plotting widgets.
inline constexpr const char* exc_error_configuring_plot {"Unable to configure plot scene."};
inline constexpr const char* exc_error_initialing_plot_scene {"Unable to render the basic "
    "elements of the scene."};
inline constexpr const char* exc_error_building_plot{ "Unable to build plot components." };
inline constexpr const char* exc_error_rendering_plot {"Unable to render plot scene."};
inline constexpr const char* exc_error_rendering_legend_box {"Unable to render legend."};
inline constexpr const char* exc_error_rendering_angular_axis {"Unable to render angular axis."};
inline constexpr const char* exc_error_rendering_radial_axis {"Unable to render radial axis."};
inline constexpr const char* exc_error_rendering_vertical_axis {"Unable to render vertical axis."};
inline constexpr const char* exc_error_rendering_horizontal_axis {"Unable to render horizontal axis."};
inline constexpr const char* exc_error_rendering_color_bar {"Unable to render color bar."};

inline constexpr const char* exc_bad_drawing_mode {"The specified drawing mode is not valid."};
inline constexpr const char* exc_bad_selection_mode {"The specified selection mode is not valid."};
inline constexpr const char* exc_bad_resize_policy {"The specified resize policy is not valid."};
inline constexpr const char* exc_bad_item_type {"The specified item type is not valid."};
inline constexpr const char* exc_bad_horizontal_units {"The specified horizontal units are not valid."};
inline constexpr const char* exc_bad_vertical_units {"The specified vertical units are not valid."};
inline constexpr const char* exc_bad_window_function {"The specified window function is not valid."};
inline constexpr const char* exc_bad_color_palette {"The specified color palette is not valid for this "
    "operation."};
inline constexpr const char* exc_bad_legend_box_position {"The specified legend box position is not valid."};
inline constexpr const char* exc_bad_color_bar_position {"The specified color bar position is not valid."};
inline constexpr const char* exc_bad_axis_position {"The specified axis position is not valid."};

inline constexpr const char* exc_bad_probability_function {"The specified probability function is not valid."};
inline constexpr const char* exc_bad_smoothing_method {"The specified smoothing method is not valid."};
inline constexpr const char* exc_bad_bounding_method {"The specified bounding method is not valid."};

inline constexpr const char* exc_bad_arrays_for_plotting {"The arrays with the data to be plotted are "
    "inconsistent."};
inline constexpr const char* exc_bad_head_arrays {"The arrays with the data and the properties of the "
    "head plot must be of the same size."};
inline constexpr const char* exc_bad_topoplot_arrays {"The arrays with the data and the properties of the "
    "topoplot must be of the same size."};
inline constexpr const char* exc_too_many_topoplots {"The number of topoplots is too big to be rendered "
    "in one scene."};

inline constexpr const char* exc_error_adding_mark {"Unable to add mark to the scene."};
inline constexpr const char* exc_error_adding_line {"Unable to add line to the scene."};
inline constexpr const char* exc_error_adding_rectangle {"Unable to add rectangle to the scene."};
inline constexpr const char* exc_error_adding_canvas {"Unable to add canvas to the scene."};
inline constexpr const char* exc_error_adding_image {"Unable to add image to the scene."};

inline constexpr const char* exc_bad_data_file {"The specified file is not valid or it does not contain "
    "data that can be plotted."};

// Strings for OpenGL scenes.
inline constexpr const char* exc_bad_color_object {"The specified color is not valid."};

inline constexpr const char* exc_bad_color_array {"The size of the color array must be same as the number "
    "of points or vertices to be rendered."};
inline constexpr const char* exc_bad_array_of_normals {"The size of the array with the normal vectors must "
    "be same as the number of vertices to be rendered."};

inline constexpr const char* exc_error_in_glenable {"OpenGL error in glEnable: "};
inline constexpr const char* exc_error_in_glClearColor {"OpenGL error in glClearColor: "};
inline constexpr const char* exc_error_initializing_vbo {"Unable to create VBO. OpenGL error: "};
inline constexpr const char* exc_error_drawing_object {"Unable to draw object. OpenGL error: "};

inline constexpr const char* exc_error_linking_shaders {"Unable to initialize and link shaders."};
inline constexpr const char* exc_error_initializing_vertex_shader {"Unable to initialize vertex shader."};
inline constexpr const char* exc_error_initializing_fragment_shader {"Unable to initialize fragment shader."};

// Strings for image tools.
inline constexpr const char* exc_bad_color_palette_size {"The size of the specified color palette is not "
    "valid for this operation."};
inline constexpr const char* exc_size_of_color_palette_is_not_256 {"The size of the specified color "
    "palette is not 256, and this function requires palettes of this size."};

inline constexpr const char* exc_non_binary_image {"The function only works with binary images."};
inline constexpr const char* exc_non_gray_scale_image {"The function only works with gray-scale images."};
inline constexpr const char* exc_non_rgb_image {"The function only works with RGB images."};
inline constexpr const char* exc_non_gray_scale_or_rgb_image {"The function only works with gray-scale or "
    "RGB images."};

// Strings for QT Styles.
inline constexpr const char* exc_bad_property {"The specified property is not valid or supported by "
    "this class."};
inline constexpr const char* exc_spread_method {"The specified spread method is not valid or supported by "
    "this class."};

// Strings for custom widgets.

inline constexpr const char* exc_bad_path {"The specified path does not exist."};
inline constexpr const char* exc_bad_file {"The specified file does not exist."};
inline constexpr const char* exc_bad_files {"One or more of the specified files don't exist."};
inline constexpr const char* exc_bad_file_name {"The specified file name is not valid."};

inline constexpr const char* exc_imposible_to_modify_list {"The list cannot be modified."};
inline constexpr const char* exc_imposible_to_resize_list {"The list cannot be resized."};
inline constexpr const char* exc_imposible_to_clear_or_resize_list {"The list cannot be cleared or resized."};


}
#endif
//=================================================================================================================
//        END OF FILE
//=================================================================================================================
