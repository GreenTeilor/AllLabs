library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity simple_mux_sim is
end simple_mux_sim;

architecture behaviour of simple_mux_sim is
component mux_b is
    port (
        a, b, s : in  STD_LOGIC;
        z : out STD_LOGIC
    );
end component;
component mux_s is
        port (
            a, b, s : in  STD_LOGIC;
            z : out STD_LOGIC
        );
end component;
signal a, b, s: STD_LOGIC;
signal q_b, q_s: STD_LOGIC;
signal error: STD_LOGIC;
signal test_vector: std_logic_vector(2 downto 0);
constant period : time := 10ns; 
begin
    UB: mux_b port map (
        a => a,
        b => b,
        s => s,
        z => q_b
    );
    US: mux_s port map (
        a => a,
        b => b,
        s => s,
        z => q_s
    );
    a <= test_vector(0);
    b <= test_vector(1);
    s <= test_vector(2);
    
    sim_proc: process
    begin
        for i in 0 to 7 loop
            test_vector <= std_logic_vector(to_unsigned(i, test_vector'length));
            wait for period;
        end loop;  
        report "End of simulation" severity failure;  
    end process;
    error <= q_b xor q_s;
end behaviour;