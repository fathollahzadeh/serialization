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
    <td rowspan="2"> External Sort Time (Min.) <b>#10M</b></td>
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
   <tr><td>Java Default</td><td>21.52</td><td>6.51</td><td>720.34</td><td>357.73</td><td>30.24</td><td>19</td><td>49.16</td></tr>
<tr><td>Java Json+Gzip</td><td>11.39</td><td>8.99</td><td>110.8</td><td>130.05</td><td>64.51</td><td>48.84</td><td>148.39</td></tr>
<tr><td>Java Bson</td><td>120.32</td><td>39.95</td><td>653.36</td><td>930.24</td><td>57.89</td><td>18.39</td><td>76.53</td></tr>
<tr><td>Java ProtoBuf</td><td>45.21</td><td>13.3</td><td>196.1</td><td>186.3</td><td>14.86</td><td>11.57</td><td>63.89</td></tr>
<tr><td>Java Kryo</td><td>34.18</td><td>11</td><td>134.94</td><td>232.39</td><td>24.3</td><td>4.84</td><td>27.02</td></tr>
<tr><td>Java Byte Buffer</td><td>28.85</td><td>11.18</td><td>465.08</td><td>779.61</td><td>18.48</td><td>6.06</td><td>49.25</td></tr>
<tr><td>Java FlatBuffers</td><td>15.95</td><td>4.34</td><td>62.12</td><td>32.82</td><td>22.31</td><td>5.38</td><td>8.07</td></tr>
<tr><td>C++ HandCoded</td><td>5.41</td><td>2.29</td><td>53.89</td><td>89.04</td><td>6.11</td><td>6.69</td><td>17.57</td></tr>
<tr><td>C++ inPlace</td><td>8.1</td><td>10.9</td><td>157.66</td><td>134.03</td><td>5</td><td>8.19</td><td>4.84</td></tr>
<tr><td>C++ Boost</td><td>3.6</td><td>1.35</td><td>67.48</td><td>67.48</td><td>4.12</td><td>7.3</td><td>18.2</td></tr>
<tr><td>C++ ProtoBuf</td><td>2.63</td><td>0.22</td><td>123.07</td><td>145.33</td><td>6.74</td><td>4.56</td><td>33.72</td></tr>
<tr><td>C++ Bson</td><td>9.5</td><td>13.17</td><td>4172.08</td><td>4458.21</td><td>28</td><td>12.21</td><td>10.18</td></tr>
<tr><td>C++ FlatBuffers</td><td>9.11</td><td>7.01</td><td>196.08</td><td>304.85</td><td>6.16</td><td>5.03</td><td>9.56</td></tr>
<tr><td>Rust Json</td><td>25.43</td><td>31.01</td><td>13707.72</td><td>13774.34</td><td>2.39</td><td>6.28</td><td>3.64</td></tr>
<tr><td>Rust Bincode</td><td>23.89</td><td>5.83</td><td>2256.03</td><td>2126.31</td><td>2.28</td><td>1.76</td><td>4.48</td></tr>
<tr><td>Rust MessagePack</td><td>9.4</td><td>1.22</td><td>639.48</td><td>701.65</td><td>1.36</td><td>1.67</td><td>7.58</td></tr>
<tr><td>Rust Bson</td><td>59.39</td><td>55.99</td><td>24811.59</td><td>3688.92</td><td>3.63</td><td>10.07</td><td>9.48</td></tr>
<tr><td>Rust FlexBuffers</td><td>34.96</td><td>37.78</td><td>9513.4</td><td>8943.54</td><td>4</td><td>2.22</td><td>9.74</td></tr>
</table>
