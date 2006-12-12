<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:include href="config.xsl"/>

<xsl:output indent="yes" method="xml" encoding="utf-8"/>

<xsl:param name="params"/>

<xsl:variable name="paramsroot" select="document($params)"/>
<xsl:variable name="entityroot" select="document(string($paramsroot//param[@name='entity']/@value))"/>


<xsl:template match="/sentences">
  <sentences>
    <xsl:apply-templates/>
  </sentences>
</xsl:template>


<xsl:template match="sentence">
  <sentence>
    <xsl:apply-templates/>
  </sentence>
</xsl:template>


<xsl:template match="ename">
  <xsl:variable name="entity" select="."/>
  
  <xsl:for-each select="$entityroot//enamedata[@symbol=$entity/@symbol]/node()">
  
    <xsl:choose>
      <xsl:when test="name(.) = 'word'">
        <word>
	  <xsl:attribute name="pattern">
	    <xsl:value-of select="@pattern"/>
	  </xsl:attribute>
	  <xsl:attribute name="class">
	    <xsl:value-of select="@class"/>
	  </xsl:attribute>
	  <xsl:if test="boolean($entity/@case)">
	    <xsl:attribute name="case">
	      <xsl:value-of select="$entity/@case"/>
	    </xsl:attribute>
	  </xsl:if>
	  <xsl:if test="boolean($entity/@number)">
	    <xsl:attribute name="number">
	      <xsl:value-of select="$entity/@number"/>
	    </xsl:attribute>
	  </xsl:if>
	  <xsl:value-of select="text()"/>
	</word>
      </xsl:when>
      <xsl:otherwise>
        <xsl:copy-of select="."/>
      </xsl:otherwise>
      
    </xsl:choose>
  </xsl:for-each>
</xsl:template>


<xsl:template match="*">
  <xsl:copy-of select="."/>
</xsl:template>


</xsl:stylesheet>