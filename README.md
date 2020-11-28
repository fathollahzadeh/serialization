# An Experimental Comparison of Complex Object Implementations for Big Data Systems

Java
--
Java Implementation is in Directory ./Java

C++
--
C++ Implementation is in Direcotry ./C++ 

Rust
--
Rust Implementation is in Direcotry ./Rust 


Standard Deviation of Experiments
--
The table below present the standard deviation of the experiments.

<table>  
  <tr>
    <td rowspan="3">Method</td>
    <td colspan="4">Read Time (Sec.) <b>#4M</b></td>
    <td colspan="2" rowspan="2" >Write Time (Sec.) <b>#5M</b></td>
    <td rowspan="2"> External Sort Time (Sec.) <b>#10M</b></td>
  </tr> 
  <tr>
    <td colspan="2">Sequential</td>
    <td colspan="2">Random</td>
  </tr>
  <tr>
    <td >ts=True</td>
    <td >ts=False</td>
    <td >ts=True</td>
    <td >ts=False</td>
    <td >ts=True</td>
    <td >ts=False</td>
    <td >ts=True</td>    
  </tr>   
<tr><td>Java Default</td><td>1548.11(21.52)</td><td>662.97(6.51)</td><td>25397.37(720.34)</td><td>24927.58(357.73)</td><td>583.85(30.24)</td><td>424.78(19)</td><td>7412.91(49.16)</td></tr>
<tr><td>Java Json+Gzip</td><td>1451.71(11.39)</td><td>612.98(8.99)</td><td>5202.08(110.8)</td><td>4922.71(130.05)</td><td>2060.56(64.51)</td><td>1620.41(48.84)</td><td>11985.22(148.39)</td></tr>
<tr><td>Java Bson</td><td>1137.91(120.32)</td><td>391.34(39.95)</td><td>27060.17(653.36)</td><td>27080.15(930.24)</td><td>847.16(57.89)</td><td>421.62(18.39)</td><td>6775.98(76.53)</td></tr>
<tr><td>Java ProtoBuf</td><td>426.09(45.21)</td><td>152.15(13.3)</td><td>6099.08(196.1)</td><td>6187.56(186.3)</td><td>313.46(14.86)</td><td>165.59(11.57)</td><td>4976.94(63.89)</td></tr>
<tr><td>Java Kryo</td><td>397.18(34.18)</td><td>157.81(11)</td><td>6896.55(134.94)</td><td>7145.89(232.39)</td><td>201.17(24.3)</td><td>122.54(4.84)</td><td>5298.53(27.02)</td></tr>
<tr><td>Java Byte Buffer</td><td>512.83(28.85)</td><td>269.8(11.18)</td><td>13292.94(465.08)</td><td>14052.2(779.61)</td><td>255.73(18.48)</td><td>139.94(6.06)</td><td>4423.69(49.25)</td></tr>
<tr><td>Java FlatBuffers</td><td>115.3(15.95)</td><td>85.44(4.34)</td><td>1229.48(62.12)</td><td>1167(32.82)</td><td>268.64(22.31)</td><td>176.81(5.38)</td><td>3094.04(8.07)</td></tr>
<tr><td>C++ HandCoded</td><td>63.2(5.41)</td><td>67.14(2.29)</td><td>1281.76(53.89)</td><td>1311.75(89.04)</td><td>56.32(6.11)</td><td>32.69(6.69)</td><td>493.19(17.57)</td></tr>
<tr><td>C++ inPlace</td><td>93.1(8.1)</td><td>90.86(10.9)</td><td>1957.31(157.66)</td><td>1978.4(134.03)</td><td>79.36(5)</td><td>43.1(8.19)</td><td>490.88(4.84)</td></tr>
<tr><td>C++ Boost</td><td>175.02(3.6)</td><td>181.4(1.35)</td><td>1525.12(67.48)</td><td>1546.27(67.48)</td><td>419.8(4.12)</td><td>210.31(7.3)</td><td>1772.78(18.2)</td></tr>
<tr><td>C++ ProtoBuf</td><td>70.04(2.63)</td><td>79.04(0.22)</td><td>1813.28(123.07)</td><td>1818.47(145.33)</td><td>164.62(6.74)</td><td>83.69(4.56)</td><td>767.64(33.72)</td></tr>
<tr><td>C++ Bson</td><td>1116.96(9.5)</td><td>1120(13.17)</td><td>44791.37(4172.08)</td><td>44446(4458.21)</td><td>2345.63(28)</td><td>1195.31(12.21)</td><td>9389(10.18)</td></tr>
<tr><td>C++ FlatBuffers</td><td>89.31(9.11)</td><td>87.93(7.01)</td><td>3080.16(196.08)</td><td>3056.92(304.85)</td><td>111.62(6.16)</td><td>70.09(5.03)</td><td>598.09(9.56)</td></tr>
<tr><td>Rust Json</td><td>436.46(25.43)</td><td>423.07(31.01)</td><td>30977.3(13707.72)</td><td>31375.45(13774.34)</td><td>103.41(2.39)</td><td>107.21(6.28)</td><td>1628.23(3.64)</td></tr>
<tr><td>Rust Bincode</td><td>272.7(23.89)</td><td>252.76(5.83)</td><td>5244.98(2256.03)</td><td>5238.93(2126.31)</td><td>44.51(2.28)</td><td>43.11(1.76)</td><td>1123.15(4.48)</td></tr>
<tr><td>Rust MessagePack</td><td>258.71(9.4)</td><td>241.93(1.22)</td><td>1801.61(639.48)</td><td>1802.6(701.65)</td><td>39.06(1.36)</td><td>39.29(1.67)</td><td>1133.88(7.58)</td></tr>
<tr><td>Rust Bson</td><td>821.09(59.39)</td><td>804.26(55.99)</td><td>58345.17(24811.59)</td><td>74074.28(3688.92)</td><td>457.23(3.63)</td><td>459.53(10.07)</td><td>4755.21(9.48)</td></tr>
<tr><td>Rust FlexBuffers</td><td>400.33(34.96)</td><td>389.32(37.78)</td><td>24685.26(9513.4)</td><td>24480.01(8943.54)</td><td>301.21(4)</td><td>297.82(2.22)</td><td>2036.47(9.74)</td></tr>
</table>
