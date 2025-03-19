library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity complex_mux_sim is
end complex_mux_sim;

architecture behaviour of complex_mux_sim is
component complex_mux_b is
    port (
        a, b, a1, b1, s : in  STD_LOGIC;
        z, z1 : out STD_LOGIC
    );
end component;
component complex_mux_s is
    port (
        a, b, a1, b1, s : in  STD_LOGIC;
        z, z1 : out STD_LOGIC
    );
end component;
signal a, b, a1, b1, s: STD_LOGIC;
signal q_b, q1_b, q_s, q1_s: STD_LOGIC;
signal error: STD_LOGIC;
signal test_vector: std_logic_vector(4 downto 0);
constant period : time := 10ns; 
begin
    UB: complex_mux_b port map (
        a => a,
        b => b,
        a1 => a1,
        b1 => b1,
        s => s,
        z => q_b,
        z1 => q1_b
    );
    US: complex_mux_s port map (
        a => a,
        b => b,
        a1 => a1,
        b1 => b1,
        s => s,
        z => q_s,
        z1 => q1_s
    );
    a <= test_vector(0);
    b <= test_vector(1);
    a1 <= test_vector(2);
    b1 <= test_vector(3);
    s <= test_vector(4);
    
    sim_proc: process
    begin
        for i in 0 to 31 loop
            test_vector <= std_logic_vector(to_unsigned(i, test_vector'length));
            wait for period;
        end loop;  
        report "End of simulation" severity failure;  
    end process;
    error <= (q_b xor q_s) or (q1_b xor q1_s);
end behaviour;