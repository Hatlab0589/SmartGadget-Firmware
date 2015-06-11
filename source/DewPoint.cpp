/*Copyright (c) 2015, Sensirion AG
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of Sensirion AG nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.*/

#include "DewPoint.h"

const unsigned int DewPoint::DewPLookUp[21][41] = {
  {210, 283, 340, 375, 400, 420, 437, 451, 464, 475, 485, 495, 503, 511, 518, 525, 532, 538, 544, 549, 554, 559, 564, 569, 573, 577, 581, 585, 589, 593, 597, 600, 603, 607, 610, 613, 616, 619, 622, 625, 628},
  {297, 376, 439, 477, 505, 527, 545, 561, 575, 587, 599, 609, 618, 627, 635, 643, 650, 656, 663, 669, 675, 680, 686, 691, 696, 700, 705, 709, 713, 718, 722, 725, 729, 733, 736, 740, 743, 746, 750, 753, 756},
  {382, 468, 536, 578, 609, 633, 653, 670, 685, 699, 711, 722, 733, 742, 751, 759, 767, 775, 782, 788, 795, 801, 807, 812, 818, 823, 828, 833, 837, 842, 846, 851, 855, 859, 863, 866, 870, 874, 877, 881, 884},
  {466, 559, 633, 678, 711, 738, 760, 778, 795, 810, 823, 835, 846, 857, 867, 876, 884, 892, 900, 907, 914, 921, 928, 934, 940, 945, 951, 956, 961, 966, 971, 976, 980, 985, 989, 993, 997, 1001, 1005, 1009, 1012},
  {549, 649, 728, 777, 813, 842, 865, 886, 904, 920, 934, 948, 960, 971, 982, 992, 1001, 1010, 1018, 1026, 1034, 1041, 1048, 1055, 1061, 1067, 1073, 1079, 1085, 1090, 1095, 1100, 1105, 1110, 1115, 1120, 1124, 1128, 1133, 1137, 1141},
  {630, 737, 822, 875, 914, 945, 970, 992, 1012, 1029, 1045, 1059, 1072, 1085, 1096, 1107, 1117, 1127, 1136, 1144, 1153, 1161, 1168, 1175, 1182, 1189, 1196, 1202, 1208, 1214, 1220, 1225, 1231, 1236, 1241, 1246, 1251, 1256, 1260, 1265, 1269},
  {709, 824, 915, 972, 1013, 1047, 1074, 1098, 1119, 1138, 1155, 1170, 1184, 1198, 1210, 1222, 1233, 1243, 1253, 1262, 1271, 1280, 1288, 1296, 1303, 1311, 1318, 1325, 1331, 1338, 1344, 1350, 1356, 1361, 1367, 1372, 1378, 1383, 1388, 1393, 1397},
  {788, 910, 1007, 1068, 1112, 1148, 1177, 1203, 1226, 1246, 1264, 1281, 1296, 1310, 1324, 1336, 1348, 1359, 1370, 1380, 1389, 1399, 1408, 1416, 1424, 1432, 1440, 1447, 1454, 1461, 1468, 1474, 1481, 1487, 1493, 1499, 1504, 1510, 1515, 1521, 1526},
  {864, 994, 1098, 1163, 1210, 1248, 1280, 1307, 1331, 1353, 1372, 1390, 1407, 1422, 1437, 1450, 1463, 1475, 1486, 1497, 1507, 1517, 1527, 1536, 1545, 1553, 1561, 1569, 1577, 1584, 1592, 1599, 1606, 1612, 1619, 1625, 1631, 1637, 1643, 1649, 1654},
  {940, 1077, 1188, 1256, 1307, 1348, 1381, 1411, 1436, 1459, 1480, 1499, 1517, 1534, 1549, 1563, 1577, 1590, 1602, 1614, 1625, 1635, 1646, 1656, 1665, 1674, 1683, 1691, 1700, 1708, 1715, 1723, 1730, 1737, 1744, 1751, 1758, 1764, 1770, 1777, 1783},
  {1014, 1159, 1276, 1349, 1403, 1446, 1482, 1513, 1541, 1565, 1588, 1608, 1627, 1644, 1661, 1676, 1691, 1705, 1718, 1730, 1742, 1753, 1764, 1775, 1785, 1795, 1804, 1813, 1822, 1831, 1839, 1847, 1855, 1863, 1870, 1877, 1884, 1891, 1898, 1905, 1911},
  {1088, 1240, 1364, 1441, 1498, 1544, 1582, 1615, 1644, 1671, 1694, 1716, 1736, 1755, 1772, 1789, 1804, 1819, 1833, 1846, 1859, 1871, 1883, 1894, 1905, 1915, 1925, 1935, 1944, 1953, 1962, 1971, 1979, 1988, 1996, 2003, 2011, 2018, 2025, 2033, 2039},
  {1159, 1320, 1451, 1532, 1593, 1641, 1681, 1716, 1747, 1775, 1800, 1823, 1845, 1864, 1883, 1901, 1917, 1933, 1947, 1962, 1975, 1988, 2001, 2012, 2024, 2035, 2046, 2056, 2066, 2076, 2086, 2095, 2104, 2112, 2121, 2129, 2137, 2145, 2153, 2161, 2168},
  {1230, 1399, 1536, 1622, 1686, 1737, 1780, 1817, 1850, 1879, 1906, 1930, 1953, 1974, 1993, 2012, 2029, 2046, 2062, 2077, 2091, 2105, 2118, 2131, 2143, 2155, 2166, 2177, 2188, 2199, 2209, 2218, 2228, 2237, 2246, 2255, 2264, 2272, 2280, 2289, 2296},
  {1300, 1477, 1621, 1711, 1778, 1832, 1877, 1917, 1951, 1982, 2010, 2036, 2060, 2082, 2103, 2123, 2141, 2159, 2176, 2192, 2207, 2221, 2236, 2249, 2262, 2275, 2287, 2298, 2310, 2321, 2332, 2342, 2352, 2362, 2372, 2381, 2390, 2399, 2408, 2416, 2425},
  {1368, 1553, 1705, 1800, 1870, 1927, 1974, 2016, 2052, 2085, 2115, 2142, 2167, 2191, 2213, 2233, 2253, 2272, 2289, 2306, 2322, 2338, 2353, 2367, 2381, 2394, 2407, 2419, 2431, 2443, 2454, 2465, 2476, 2487, 2497, 2507, 2517, 2526, 2535, 2544, 2553},
  {1436, 1629, 1787, 1887, 1961, 2020, 2071, 2114, 2152, 2187, 2218, 2247, 2273, 2298, 2322, 2343, 2364, 2384, 2402, 2420, 2437, 2454, 2469, 2484, 2499, 2513, 2527, 2540, 2553, 2565, 2577, 2589, 2600, 2611, 2622, 2633, 2643, 2653, 2663, 2672, 2682},
  {1502, 1704, 1869, 1973, 2051, 2113, 2166, 2211, 2252, 2288, 2321, 2351, 2379, 2405, 2430, 2453, 2475, 2495, 2515, 2534, 2552, 2569, 2586, 2602, 2617, 2632, 2646, 2660, 2674, 2687, 2699, 2712, 2724, 2736, 2747, 2758, 2769, 2780, 2790, 2800, 2810},
  {1567, 1777, 1950, 2059, 2140, 2205, 2261, 2308, 2351, 2389, 2423, 2455, 2485, 2512, 2538, 2562, 2585, 2607, 2628, 2647, 2666, 2684, 2702, 2719, 2735, 2751, 2766, 2780, 2795, 2808, 2822, 2835, 2848, 2860, 2872, 2884, 2895, 2907, 2918, 2928, 2939},
  {1631, 1850, 2030, 2144, 2228, 2297, 2355, 2405, 2449, 2489, 2525, 2558, 2589, 2618, 2645, 2671, 2695, 2718, 2739, 2760, 2780, 2799, 2818, 2835, 2852, 2869, 2885, 2900, 2915, 2930, 2944, 2958, 2971, 2984, 2997, 3009, 3021, 3033, 3045, 3056, 3067},
  {1695, 1922, 2109, 2227, 2316, 2387, 2448, 2500, 2546, 2588, 2626, 2661, 2694, 2724, 2752, 2779, 2804, 2828, 2851, 2873, 2894, 2914, 2933, 2952, 2970, 2987, 3004, 3020, 3036, 3051, 3066, 3080, 3095, 3108, 3122, 3135, 3148, 3160, 3172, 3184, 3196}
};

float DewPoint::calculateDewPoint(float humi, float temp)
{
  uint16_t aTicksHumi;
  uint16_t aTicksTemp;

  uint8_t Humi_val;
  uint8_t Humi_addr;
  uint16_t Temp_val;
  uint8_t Temp_addr;
  float DewPointC; // variable for result

  uint32_t I0;
  uint32_t I1;


  temp += 50;
  if (temp < 0)temp = 0;
  if (temp > 200)temp = 200;

  aTicksHumi = static_cast<uint16_t>(100 * humi);
  aTicksTemp = static_cast<uint16_t>(100 * temp);

  // save absolute values vo Lookup-Table

  Humi_val = 0x00FF & aTicksHumi; // Humi Value Bit0-7		
  Humi_addr = aTicksHumi >> 8; // Humi LookUp-Adresse Bit8-15
  Temp_val = 0x03FF & aTicksTemp; // Temp Value Bit0-9
  Temp_addr = aTicksTemp >> 10; // Temp LookUp-Adresse Bit10-13


  I1 = (DewPLookUp[Temp_addr + 1][Humi_addr] << 3) +
    (((DewPLookUp[Temp_addr + 1][Humi_addr + 1] - DewPLookUp[Temp_addr + 1][Humi_addr]) * Humi_val) >> 5);

  I0 = (DewPLookUp[Temp_addr][Humi_addr] << 3) +
    (((DewPLookUp[Temp_addr][Humi_addr + 1] - DewPLookUp[Temp_addr][Humi_addr]) * Humi_val) >> 5);


  DewPointC = static_cast<float>((static_cast<uint16_t>(I0) + static_cast<uint16_t>((static_cast<uint32_t>(I1 - I0) * static_cast<uint32_t>(Temp_val)) >> 10)) - 10000) / 100;


  return DewPointC;
}