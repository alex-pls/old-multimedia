#pragma once

using namespace System;


namespace vipPS
{
	public __gc class vipDirectories {
			public:
				String* current;
				String* vipRoot;
				String* vipSource;
				String* vipBinaries;
				String* vipTests;
				String* packages;
				String* packagesTemplate;
			};
}
