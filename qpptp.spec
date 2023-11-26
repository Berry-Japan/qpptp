%define name qpptp
%define version 0.13
%define release b1

Name:		%{name}
Summary:	PPTP for Berry Linux
Version:	%{version}
Release:	%{release}
License:	GPL
Group:		System/Tools
Source:		%{name}-%{version}.tar.bz2
Buildroot:	%{_tmppath}/%{name}-%{version}

BuildArchitectures: i586

%description
PPTP for Berry Linux

%prep
%setup -q

%build
qmake
sed -e "s/-O2 -g/-Os/g; s/-march=i386/-march=i586/g" -i Makefile
make

%install
mkdir -p %{buildroot}/opt/berry
strip qpptp
install -m 755 qpptp %{buildroot}/opt/berry/
install -m 755 qpptp*.qm %{buildroot}/opt/berry/

mkdir -p %{buildroot}/usr/share/applications/Berry
install -m 644 *.desktop %{buildroot}/usr/share/applications/Berry

%clean
[ -n "%{buildroot}" -a "%{buildroot}" != / ] && rm -rf %{buildroot}
rm -rf $RPM_BUILD_DIR/%{name}-%{version}

%files
%defattr (-,root,root)
/opt/berry/*
/usr/share/applications/Berry/*.desktop

%changelog
* Tue Oct 16 2007 Yuichiro Nakada <berry@po.yui.mine.nu>
- English support (0.7)
* Sun Jan 7 2007 Yuichiro Nakada <berry@po.yui.mine.nu>
- Create for Berry Linux
