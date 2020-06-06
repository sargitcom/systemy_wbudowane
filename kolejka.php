<?php

function printMask($mask)
{
    echo $mask['8'] . $mask['7'] . $mask['6'] . $mask['5'] . $mask['4'] . $mask['3'] . $mask['2'] . $mask['1'] . "\n";
}

function clearMaskFromNthPosition(&$mask, $position)
{
    for ($i = $position - 1; $i > 0; $i--) {
        $mask[$i] = 0;
    }
}

$mask = [];
$mask['8'] = 0;
$mask['7'] = 0;
$mask['6'] = 0;
$mask['5'] = 0;
$mask['4'] = 0;
$mask['3'] = 0;
$mask['2'] = 0;
$mask['1'] = 1;


for ($j = 8; $j >= 1; $j--) {
    for ($i = 1; $i <= $j; $i++) {
        $mask[$i] = 1;
        clearMaskFromNthPosition($mask, $i);
        printMask($mask);
    }
}