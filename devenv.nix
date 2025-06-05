{ pkgs, lib, config, inputs, ... }:

{
  # https://devenv.sh/packages/
  packages = [
    pkgs.git
	pkgs.gcc14
	];
  languages.cplusplus = {
    enable = true;
  };
}
