import pytest
from main import find_maximum_number 

def test_find_maximum_number_empty_list():
    sum_of_number_arrays = []
    result = find_maximum_number(sum_of_number_arrays)
    assert result is None, f"Expected None, but got {result}"

def test_find_maximum_number_valid_input():
    sum_of_number_arrays = [10, 20, 30, 40, 50]
    expected_result = 50
    result = find_maximum_number(sum_of_number_arrays)
    assert result == expected_result, f"Expected {expected_result}, but got {result}"

def test_find_maximum_number_negative_numbers():
    sum_of_number_arrays = [-10, -20, -30, -40, -50]
    expected_result = -10
    result = find_maximum_number(sum_of_number_arrays)
    assert result == expected_result, f"Expected {expected_result}, but got {result}"

def test_find_maximum_number_mixed_input():
    sum_of_number_arrays = [10, -20, 30, -40, 50]
    expected_result = 50
    result = find_maximum_number(sum_of_number_arrays)
    assert result == expected_result, f"Expected {expected_result}, but got {result}"

def test_find_maximum_number_with_non_integers():
    # Given
    non_integer_input = [1, 2, 3, "four"]
    # When
    with pytest.raises(ValueError) as exception_info:
        find_maximum_number(non_integer_input)
    # Then
    assert str(exception_info.value) == "Input must be an array of integers."

