<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:include href="config.xsl"/>

<xsl:output indent="yes" method="xml" encoding="utf-8"/>

<xsl:param name="params"/>

<xsl:variable name="paramsroot" select="document($params)"/>
<xsl:variable name="ruleroot" select="document(string($paramsroot//param[@name='rule']/@value))"/>
<xsl:variable name="numofant" select="$paramsroot//param[@name='numofant']/@value"/>
<xsl:variable name="numofsuc" select="$paramsroot//param[@name='numofsuc']/@value"/>


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


<xsl:template match="*">
  <xsl:copy-of select="."/>
</xsl:template>


<xsl:template match="literal">
  <xsl:variable name="type" select="@role"/>
  <xsl:variable name="position" select="count(preceding-sibling::literal[@role=$type]) + 1"/>
  <xsl:variable name="attr" select="$ruleroot//cedent[@type=$type]/literal[position()=$position]/@attribute"/>
  <xsl:variable name="val" select="$ruleroot//cedent[@type=$type]/literal[position()=$position]/coefficient/value"/>
 
 <literal>

 <xsl:choose>
 
 <xsl:when test="$attr != ''">
 	<xsl:attribute name="mbattribute">
      <xsl:value-of select="$attr"/>
    </xsl:attribute>
    <xsl:attribute name="value">
      <xsl:value-of select="$val"/> 
	 </xsl:attribute>
 </xsl:when>
 
 <xsl:otherwise>
	<xsl:choose>
	
	<xsl:when test="$type = 'S'">
		<xsl:variable name="position2" select="count(preceding-sibling::literal[@role=$type]) - $numofsuc + 1"/>
		<xsl:variable name="attr2" select="$ruleroot//cedent[@type=$type]/literal[position()=$position2]/@attribute"/>
  		<xsl:variable name="val2" select="$ruleroot//cedent[@type=$type]/literal[position()=$position2]/coefficient/value"/> 	
		 
	<xsl:attribute name="mbattribute">
    	  	<xsl:value-of select="$attr2"/>
  	</xsl:attribute>
 	<xsl:attribute name="value">
 	   		<xsl:value-of select="$val2"/>
	</xsl:attribute>
 	</xsl:when>
	
	<xsl:when test="$type = 'A'">
		<xsl:variable name="position2" select="count(preceding-sibling::literal[@role=$type]) - $numofant + 1"/>
		<xsl:variable name="attr2" select="$ruleroot//cedent[@type=$type]/literal[position()=$position2]/@attribute"/>
	  	<xsl:variable name="val2" select="$ruleroot//cedent[@type=$type]/literal[position()=$position2]/coefficient/value"/> 	  
		 
	<xsl:attribute name="mbattribute">
    	  	<xsl:value-of select="$attr2"/>
  	</xsl:attribute>
 	<xsl:attribute name="value">
 	   		<xsl:value-of select="$val2"/>
	</xsl:attribute>
	</xsl:when>
	</xsl:choose>
	
</xsl:otherwise>

</xsl:choose>

	<xsl:attribute name="role">
      <xsl:value-of select="@role"/>
    </xsl:attribute>
    <xsl:attribute name="typeofphrase">
      <xsl:value-of select="@typeofphrase"/>
    </xsl:attribute>
    <xsl:if test="@number">
      <xsl:attribute name="number">
        <xsl:value-of select="@number"/>
      </xsl:attribute>
    </xsl:if>
    <xsl:if test="@case">
      <xsl:attribute name="case">
        <xsl:value-of select="@case"/>
      </xsl:attribute>
    </xsl:if>
    <xsl:if test="@vderivation">
      <xsl:attribute name="vderivation">
        <xsl:value-of select="@vderivation"/>
      </xsl:attribute>
    </xsl:if>
  
  
  </literal>
</xsl:template>


</xsl:stylesheet>