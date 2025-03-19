library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity summator_2_sim is
end summator_2_sim;

architecture behaviour of summator_2_sim is
component summator_2_b is
    port (
        x1, x2, x3, x4, x5 : in  STD_LOGIC;
        y1, y2, y3 : out STD_LOGIC
    );
end component;
component summator_2_s is
    port (
        x1, x2, x3, x4, x5 : in  STD_LOGIC;
        y1, y2, y3 : out STD_LOGIC
    );
end component;
signal x1, x2, x3, x4, x5: STD_LOGIC;
signal y1_b, y2_b, y3_b: STD_LOGIC;
signal y1_s, y2_s, y3_s: STD_LOGIC;
signal error: STD_LOGIC;
signal test_vector: std_logic_vector(4 downto 0);
constant period : time := 10ns; 
begin
    UB: summator_2_b port map (
        x1 => x1,
        x2 => x2,
        x3 => x3,
        x4 => x4,
        x5 => x5,
        y1 => y1_b,
        y2 => y2_b,
        y3 => y3_b
    );
    US: summator_2_s port map (
        x1 => x1,
        x2 => x2,
        x3 => x3,
        x4 => x4,
        x5 => x5,
        y1 => y1_s,
        y2 => y2_s,
        y3 => y3_s
    );
    x1 <= test_vector(0);
    x2 <= test_vector(1);
    x3 <= test_vector(2);
    x4 <= test_vector(3);
    x5 <= test_vector(4);
    
    sim_proc: process
    begin
        for i in 0 to 31 loop
            test_vector <= std_logic_vector(to_unsigned(i, test_vector'length));
            wait for period;
        end loop;  
        report "End of simulation" severity failure;  
    end process;
    error <= (y1_b xor y1_s) or (y2_b xor y2_s) or (y3_b xor y3_s);
end behaviour;