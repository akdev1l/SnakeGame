%define debug_package %{nil}

Name:           snake-game
Version:        0.0.1
Release:        1%{?dist}
Summary:        Snake Game Clone

License:        GPL
URL:            http://akdev.xyz/%{name}-%{version}.tar.gz
Source0:        %{name}-%{version}.tar.gz

BuildRequires:  ncurses-devel gcc-c++
Requires:       ncurses

%description
Small Snake Clone

%prep
%autosetup


%build
%make_build


%install
rm -rf $RPM_BUILD_ROOT
make install PREFIX=%{buildroot}/

%define snake_bin %{_bindir}/snake-game

%files
%{snake_bin}



%changelog
* Tue Dec 25 2018 Alex Diaz <alex@akdev.xyz>
- 
