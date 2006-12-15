<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:output indent="yes" method="xml" encoding="utf-8"/>

<xsl:template match="/">

<randomness>
<xsl:for-each select="//random">
  <random number="{@number}">
  <xsl:choose>
    <xsl:when test="@number &gt; @lastvalue">
      <xsl:attribute name="lastvalue">
        <xsl:value-of select="@lastvalue + 1"/>
      </xsl:attribute>
    </xsl:when>
    <xsl:otherwise>
      <xsl:attribute name="lastvalue">1</xsl:attribute>
    </xsl:otherwise>
  </xsl:choose>
  </random>
</xsl:for-each>
</randomness>

</xsl:template>

</xsl:stylesheet>