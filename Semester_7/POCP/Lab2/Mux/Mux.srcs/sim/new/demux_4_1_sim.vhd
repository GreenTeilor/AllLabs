library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity demux_4_1_sim is
end demux_4_1_sim;

architecture behaviour of demux_4_1_sim is
component demux_4_1_b is
    port (
        s, s1, z : in  STD_LOGIC;
        a, b, c, d : out STD_LOGIC
    );
end component;
component demux_4_1_s is
    port (
        s, s1, z : in  STD_LOGIC;
        a, b, c, d : out STD_LOGIC
    );
end component;
signal s, s1, z: STD_LOGIC;
signal a_b, b_b, c_b, d_b: STD_LOGIC;
signal a_s, b_s, c_s, d_s: STD_LOGIC;
signal error: STD_LOGIC;
signal test_vector: std_logic_vector(2 downto 0);
constant period : time := 10ns; 
begin
    UB: demux_4_1_b port map (
        s => s,
        s1 => s1,
        z => z,
        a => a_b,
        b => b_b,
        c => c_b,
        d => d_b
    );
    US: demux_4_1_s port map (
        s => s,
        s1 => s1,
        z => z,
        a => a_s,
        b => b_s,
        c => c_s,
        d => d_s
    );
    s <= test_vector(0);
    s1 <= test_vector(1);
    z <= test_vector(2);
    
    sim_proc: process
    begin
        for i in 0 to 15 loop
            test_vector <= std_logic_vector(to_unsigned(i, test_vector'length));
            wait for period;
        end loop;  
        report "End of simulation" severity failure;  
    end process;
    error <= (a_b xor a_s) or (b_b xor b_s) or (c_b xor c_s) or (d_b xor d_s);
end behaviour;