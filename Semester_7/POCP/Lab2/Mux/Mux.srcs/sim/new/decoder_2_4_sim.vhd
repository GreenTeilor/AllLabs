library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity decoder_2_4_mux_sim is
end decoder_2_4_mux_sim;

architecture behaviour of decoder_2_4_mux_sim is
component decoder_2_4_s is
    port (
        s0, s1, c : in  STD_LOGIC;
        z0, z1, z2, z3 : out STD_LOGIC
    );
end component;
component decoder_2_4_b is
    port (
        s0, s1, c : in  STD_LOGIC;
        z0, z1, z2, z3 : out STD_LOGIC
    );
end component;
signal s0, s1, c: STD_LOGIC;
signal z0_b, z1_b, z2_b, z3_b: STD_LOGIC;
signal z0_s, z1_s, z2_s, z3_s: STD_LOGIC;
signal error: STD_LOGIC;
signal test_vector: std_logic_vector(2 downto 0);
constant period : time := 10ns; 
begin
    US: decoder_2_4_s port map (
       s0 => s0,
       s1 => s1,
       c => c,
       z0 => z0_s,
       z1 => z1_s,
       z2 => z2_s,
       z3 => z3_s
    );
    UB: decoder_2_4_b port map (
           s0 => s0,
           s1 => s1,
           c => c,
           z0 => z0_b,
           z1 => z1_b,
           z2 => z2_b,
           z3 => z3_b
    );
    s0 <= test_vector(0);
    s1 <= test_vector(1);
    c <= test_vector(2);
    
    sim_proc: process
    begin
        for i in 0 to 7 loop
            test_vector <= std_logic_vector(to_unsigned(i, test_vector'length));
            wait for period;
        end loop;  
        report "End of simulation" severity failure;  
    end process;
    error <= (z0_b xor z0_s) or (z1_b xor z1_s) or (z2_b xor z2_s) or (z3_b xor z3_s);
end behaviour;