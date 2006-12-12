<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:include href="config.xsl"/>

<xsl:output indent="yes" method="xml" encoding="utf-8"/>

<xsl:param name="params"/>

<xsl:variable name="paramsroot" select="document($params)"/>
<xsl:variable name="numofant" select="$paramsroot//param[@name='numofant']/@value"/>
<xsl:variable name="numofsuc" select="$paramsroot//param[@name='numofsuc']/@value"/>
<xsl:variable name="numofcon" select="$paramsroot//param[@name='numofcon']/@value"/>
<xsl:variable name="forroot" select="document($_foreach)"/>

<xsl:variable name="langparamroot" select="document(string($paramsroot//param[@name='langparam']/@value))"/>
<xsl:variable name="conjunction" select="$langparamroot//langparam[@name='conjunction']/@value"/>

<xsl:variable name="left" select="$numofant - 1"/>
<xsl:variable name="right" select="1"/>


<xsl:template match="/">
  <sentences>
  <xsl:for-each select="//sentence">
  
    <xsl:if test="$numofant = 1">
		 <xsl:choose>
		<xsl:when test="($numofsuc &gt; 1) or ($numofcon &gt; 1)">
			<xsl:call-template name="extendliteral"/>
		</xsl:when>
		<xsl:otherwise>
			<xsl:copy-of select="."/>
		</xsl:otherwise>
		</xsl:choose>
    </xsl:if>
    
    <xsl:if test="$numofant = 2">
      <xsl:choose>
	<!-- "obycejne" rozsireni literalu -->
	<xsl:when test="count(literal[@role='A']) = 1">
	  <xsl:call-template name="extendliteral"/>
	</xsl:when>

	<!--  -->
	<xsl:otherwise>
	  <xsl:copy-of select="."/>
	</xsl:otherwise>
      </xsl:choose>
    </xsl:if>
    
    <xsl:if test="$numofant &gt; 2">
      <xsl:choose>
	<!-- "obycejne" rozsireni literalu -->
	<xsl:when test="count(literal[@role='A']) = 1">
	  <xsl:call-template name="extendliteral"/>
	</xsl:when>
	<!-- "presouvani" literalu -->
	<xsl:otherwise>
	  <xsl:call-template name="moveliteral">
	    <xsl:with-param name="left" select="$left"/>
	    <xsl:with-param name="right" select="$right"/>
	  </xsl:call-template>
	</xsl:otherwise>
      </xsl:choose>
    </xsl:if>
  
  </xsl:for-each>
  </sentences>
</xsl:template>


<!-- predpoklad: sukcedenty neni zatim nutno rozsirovat touhle sablonou, k tomu
     slouzi sablona "extendliteral" -->
<xsl:template name="moveliteral">
  <xsl:param name="left"/>
  <xsl:param name="right"/>
  <sentence>
    <xsl:for-each select="node()">
      
      <xsl:choose>
        <xsl:when test="name() = 'literal'">
      
	  <xsl:choose>
	    <!-- prvni literal ve FP -->
	    <xsl:when test="(@role='A') and following-sibling::literal[@role='A']">
	      <!-- ulozime kontext -->
	      <xsl:variable name="context" select="."/>
	      <xsl:for-each select="$forroot/foreach/number[@to=$left]/val">
	        
		<xsl:call-template name="printliteral">
		  <xsl:with-param name="context" select="$context"/>
		</xsl:call-template>
		
		<xsl:call-template name="printseparator">
		  <xsl:with-param name="position" select="position()"/>
		  <xsl:with-param name="last" select="last()"/>
		</xsl:call-template>
	      </xsl:for-each>
	      
	    </xsl:when>

	    <!-- druhy literal ve FP -->
	    <xsl:when test="(@role='A') and boolean(following-sibling::literal[@role='A']) = false">
	      <!-- ulozime kontext -->
	      <xsl:variable name="context" select="."/>
	      <xsl:for-each select="$forroot/foreach/number[@to=$right]/val">
	        
		<xsl:call-template name="printliteral">
		  <xsl:with-param name="context" select="$context"/>
		</xsl:call-template>
	        
		<xsl:call-template name="printseparator">
		  <xsl:with-param name="position" select="position()"/>
		  <xsl:with-param name="last" select="last()"/>
		</xsl:call-template>
	      </xsl:for-each>      
	    </xsl:when>
	    <!-- kopirovani sukcedentu -->
	    <xsl:when test="@role='S'">
	      <!-- ulozime kontext -->
	      <xsl:variable name="context" select="."/>
	      <xsl:for-each select="$forroot/foreach/number[@to=$numofsuc]/val">
	        
		<xsl:call-template name="printliteral">
		  <xsl:with-param name="context" select="$context"/>
		</xsl:call-template>
		
		<xsl:call-template name="printseparator">
		  <xsl:with-param name="position" select="position()"/>
		  <xsl:with-param name="last" select="last()"/>
		</xsl:call-template>
		
	      </xsl:for-each>
	    </xsl:when>
		
  	  </xsl:choose>
        
	</xsl:when>
	<!-- kopirovani ostatnich uzlu ("neliteralu") -->
	<xsl:otherwise>
	  <xsl:copy-of select="."/>
	</xsl:otherwise>  

      </xsl:choose>
      
    </xsl:for-each>
  </sentence>
  <xsl:if test="$left &gt; 1">
    <xsl:call-template name="moveliteral">
      <xsl:with-param name="left" select="$left - 1"/>
      <xsl:with-param name="right" select="$right + 1"/>
    </xsl:call-template>
  </xsl:if>
</xsl:template>


<xsl:template name="extendliteral">
  <sentence>
  
    <xsl:for-each select="node()">
      
      <xsl:choose>
        <xsl:when test="name() = 'literal'">
      
	  <xsl:choose>
	    <xsl:when test="@role='A'">
	      <!-- ulozime kontext -->
	      <xsl:variable name="context" select="."/>
	      <xsl:for-each select="$forroot/foreach/number[@to=$numofant]/val">
	        
		<xsl:call-template name="printliteral">
		  <xsl:with-param name="context" select="$context"/>
		</xsl:call-template>
		
		<xsl:call-template name="printseparator">
		  <xsl:with-param name="position" select="position()"/>
		  <xsl:with-param name="last" select="last()"/>
		</xsl:call-template>
		
	      </xsl:for-each>
	    </xsl:when>



	    <!-- kopirovani sukcedentu -->
	    <xsl:when test="@role='S'">
	    
	      <!-- ulozime kontext -->
	      <xsl:variable name="context" select="."/>
	      <xsl:for-each select="$forroot/foreach/number[@to=$numofsuc]/val">
	        
		<xsl:call-template name="printliteral">
		  <xsl:with-param name="context" select="$context"/>
		</xsl:call-template>
		
		<xsl:call-template name="printseparator">
		  <xsl:with-param name="position" select="position()"/>
		  <xsl:with-param name="last" select="last()"/>
		</xsl:call-template>
		
	      </xsl:for-each>
	    </xsl:when>
		
		<!-- kopirovani podminky -->
	    <xsl:when test="@role='C'">
	    
	      <!-- ulozime kontext -->
	      <xsl:variable name="context" select="."/>
	      <xsl:for-each select="$forroot/foreach/number[@to=$numofcon]/val">
	        
		<xsl:call-template name="printliteral">
		  <xsl:with-param name="context" select="$context"/>
		</xsl:call-template>
		
		<xsl:call-template name="printseparator">
		  <xsl:with-param name="position" select="position()"/>
		  <xsl:with-param name="last" select="last()"/>
		</xsl:call-template>
		
	      </xsl:for-each>
	    </xsl:when>
		
		
	
	  </xsl:choose>
        
	</xsl:when>
	<xsl:otherwise>
	  <!-- kopirovani ostatnich uzlu ("neliteralu") -->
	  <xsl:copy-of select="."/>
	</xsl:otherwise>
      </xsl:choose>
      
    </xsl:for-each>
  </sentence>
</xsl:template>


<xsl:template name="printliteral">
  <xsl:param name="context"/>
  <literal>
    <xsl:attribute name="role">
      <xsl:value-of select="$context/@role"/>
    </xsl:attribute>
    <xsl:attribute name="typeofphrase">
      <xsl:value-of select="$context/@typeofphrase"/>
    </xsl:attribute>
    <xsl:if test="$context/@case">
      <xsl:attribute name="case">
	<xsl:value-of select="$context/@case"/>
      </xsl:attribute>
    </xsl:if>
    <xsl:if test="$context/@number">
      <xsl:attribute name="number">
	<xsl:value-of select="$context/@number"/>
      </xsl:attribute>
    </xsl:if>
    <xsl:if test="$context/@vderivation">
      <xsl:attribute name="vderivation">
	<xsl:value-of select="$context/@vderivation"/>
      </xsl:attribute>
    </xsl:if>
  </literal>
</xsl:template>


<xsl:template name="printseparator">
  <xsl:param name="position"/>
  <xsl:param name="last"/>
  <xsl:choose>
    <xsl:when test="($position + 1) = $last">
      <xsl:text> </xsl:text>
      <xsl:value-of select="$conjunction"/>
      <xsl:text> </xsl:text>
    </xsl:when>
    <xsl:when test="$position != $last">
      <xsl:text>, </xsl:text>
    </xsl:when>
  </xsl:choose>
</xsl:template>


</xsl:stylesheet>