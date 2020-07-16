library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity lights is 
port(
	SW : in std_logic_vector(7 downto 0);
	KEY : in std_logic_vector(0 downto 0);
	CLOCK_50 : in std_logic;
	LEDG : out std_logic_vector(7 downto 0)
);
end lights;

architecture structure of lights is
component nios_system
port(
	clk : in std_logic;
	reset_n : in std_logic;
	out_port : out std_logic_vector(7 downto 0);
	in_port: in std_logic_vector(7 downto 0)
);
end component;

begin
NI2: nios_system port map (CLOCK_50, KEY(0), LEDG, SW); 
end structure;