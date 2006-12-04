<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<!-- Name and path to the file with "random numbers". -->
<xsl:param name="_randomness" select="'randomness.xml'"/>

<!-- Name and path to the file with numbers that serve as a counter for cycle
     "foreach". -->
<xsl:param name="_foreach" select="'foreach.xml'"/>

<!-- Parameter indicates whether show all sentences (value "all") or only 
     correctly transformed sentences (value "correct"). -->
<xsl:param name="_show" select="'all'"/>

</xsl:stylesheet>