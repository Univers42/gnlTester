/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:40:15 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/02/27 20:40:16 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/test_files.h"

const char *TEST_FILES[][2] = {
    {"test_cases/empty.txt", "expected_output/empty.txt"},
    {"test_cases/one_line.txt", "expected_output/one_line.txt"},
    {"test_cases/multi_lines.txt", "expected_output/multi_lines.txt"},
    {"test_cases/no_newline.txt", "expected_output/no_newline.txt"},
    {"test_cases/big_file.txt", "expected_output/big_file.txt"},
    {"test_cases/1char.txt", "expected_output/1char.txt"},
    {"test_cases/41_no_nl", "expected_output/41_no_nl"},
    {"test_cases/41_no_nl copy 2", "expected_output/41_no_nl copy 2"},
    {"test_cases/41_with_nl", "expected_output/41_with_nl"},
    {"test_cases/42_no_nl", "expected_output/42_no_nl"},
    {"test_cases/42_with_nl", "expected_output/42_with_nl"},
    {"test_cases/43_no_nl", "expected_output/43_no_nl"},
    {"test_cases/43_with_nl", "expected_output/43_with_nl"},
    {"test_cases/big_line_with_nl", "expected_output/big_line_with_nl"},
    {"test_cases/empty.txt", "expected_output/empty.txt"},
    {"test_cases/giant_line.txt", "expected_output/giant_line.txt"},
    {"test_cases/lines_around_10.txt", "expected_output/lines_around_10.txt"},
    {"test_cases/multi_lines.txt", "expected_output/multi_lines.txt"},
    {"test_cases/multiple_line_no_nl", "expected_output/multiple_line_no_nl"},
    {"test_cases/multiple_line_with_nl", "expected_output/multiple_line_with_nl"},
    {"test_cases/multiple_nl.txt", "expected_output/multiple_nl.txt"},
    {"test_cases/multiple_nlx5", "expected_output/multiple_nlx5"},
    {"test_cases/nl", "expected_output/nl"},
    {"test_cases/no_newline.txt", "expected_output/no_newline.txt"},
    {"test_cases/one_line_no_nl.txt", "expected_output/one_line_no_nl.txt"},
    {"test_cases/one_line.txt", "expected_output/one_line.txt"},
    {"test_cases/only_nl.txt", "expected_output/only_nl.txt"},
    {"test_cases/variable_nls.txt", "expected_output/variable_nls.txt"},
    {"test_cases/1-brouette.txt", "expected_output/1-brouette.txt"},
    {"test_cases/2-otarie.txt", "expected_output/2-otarie.txt"},
    {"test_cases/3-oneline.txt", "expected_output/3-oneline.txt"},
    {"test_cases/4-u.txt", "expected_output/4-u.txt"},
    {"test_cases/5-empty.txt", "expected_output/5-empty.txt"},
    {"test_cases/6-newline.txt", "expected_output/6-newline.txt"},
    {"test_cases/7-onechar.txt", "expected_output/7-onechar.txt"},
    {"test_cases/8-twochar.txt", "expected_output/8-twochar.txt"},
    {"test_cases/9-linew.txt", "expected_output/9-linew.txt"},
    {"test_cases/10-b.txt", "expected_output/10-b.txt"},
    {"test_cases/11-bg.txt", "expected_output/11-bg.txt"},
    {"test_cases/12-bigben.txt", "expected_output/12-bigben.txt"},
    {"test_cases/empty.txt", "expected_output/empty.txt"},
    {"test_cases/one_line.txt", "expected_output/one_line.txt"}
};
